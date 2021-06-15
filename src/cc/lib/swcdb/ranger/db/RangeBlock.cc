/*
 * SWC-DB© Copyright since 2019 Alex Kashirin <kashirin.alex@gmail.com>
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */


#include "swcdb/core/Checksum.h"
#include "swcdb/ranger/db/RangeBlock.h"
#include "swcdb/ranger/db/RangeBlocks.h"


namespace SWC { namespace Ranger {


SWC_CAN_INLINE
Block::Ptr Block::make(const DB::Cells::Interval& interval,
                       Blocks* blocks, State state) {
  return new Block(interval, blocks, state);
}

SWC_CAN_INLINE
Block::Block(const DB::Cells::Interval& interval,
             Blocks* blocks, State state)
            : blocks(blocks), next(nullptr), prev(nullptr),
              m_cells(
                DB::Cells::Mutable(
                  blocks->range->cfg->key_seq,
                  blocks->range->cfg->cell_versions(),
                  blocks->range->cfg->cell_ttl(),
                  blocks->range->cfg->column_type())),
              m_key_end(interval.key_end),
              m_processing(0), m_state(state), m_loader(nullptr) {
  Env::Rgr::res().more_mem_usage(size_of());
}

SWC_CAN_INLINE
Block::~Block() {
  Env::Rgr::res().less_mem_usage(
    size_of() +
    (m_cells.empty() ? 0 : m_cells.size_of_internal())
  );
}

SWC_CAN_INLINE
size_t Block::size_of() const noexcept {
  return sizeof(*this);
}

SWC_CAN_INLINE
Block::Ptr Block::ptr() {
  return this;
}

void Block::schema_update() noexcept {
  Core::ScopedLock lock(m_mutex);
  m_cells.configure(
    blocks->range->cfg->cell_versions(),
    blocks->range->cfg->cell_ttl(),
    blocks->range->cfg->column_type()
  );
}

SWC_CAN_INLINE
void Block::set_prev_key_end(const DB::Cell::Key& key) {
  m_prev_key_end.copy(key);
}

SWC_CAN_INLINE
Condition::Comp Block::cond_key_end(const DB::Cell::Key& key) const {
  Core::MutexAtomic::scope lock(m_mutex_intval);
  return DB::KeySeq::compare(m_cells.key_seq, m_key_end, key);
}

SWC_CAN_INLINE
void Block::set_key_end(const DB::Cell::Key& key) {
  Core::MutexAtomic::scope lock(m_mutex_intval);
  m_key_end.copy(key);
}

SWC_CAN_INLINE
void Block::free_key_end() {
  Core::MutexAtomic::scope lock(m_mutex_intval);
  m_key_end.free();
}

SWC_CAN_INLINE
void Block::get_key_end(DB::Cell::Key& key) const {
  Core::MutexAtomic::scope lock(m_mutex_intval);
  key.copy(m_key_end);
}

SWC_CAN_INLINE
bool Block::is_consist(const DB::Cells::Interval& intval) const {
  return
    (intval.key_end.empty() || m_prev_key_end.empty() ||
     DB::KeySeq::compare(m_cells.key_seq, m_prev_key_end, intval.key_end)
      == Condition::GT)
    &&
    (intval.key_begin.empty() || is_in_end(intval.key_begin));
}

SWC_CAN_INLINE
bool Block::is_in_end(const DB::Cell::Key& key) const {
  Core::MutexAtomic::scope lock(m_mutex_intval);
  return _is_in_end(key);
}

SWC_CAN_INLINE
bool Block::_is_in_end(const DB::Cell::Key& key) const {
  return m_key_end.empty() || (!key.empty() &&
          DB::KeySeq::compare(m_cells.key_seq, m_key_end, key)
                                              != Condition::GT);
}

SWC_CAN_INLINE
bool Block::is_next(const DB::Specs::Interval& spec) const {
  if(includes_end(spec)) {
    Core::MutexAtomic::scope lock(m_mutex_intval);
    return (spec.offset_key.empty() || _is_in_end(spec.offset_key)) &&
            _includes_begin(spec);
  }
  return false;
}

SWC_CAN_INLINE
bool Block::includes(const DB::Specs::Interval& spec) const {
  if(includes_end(spec)) {
    Core::MutexAtomic::scope lock(m_mutex_intval);
    return _includes_begin(spec);
  }
  return false;
}

SWC_CAN_INLINE
bool Block::_includes_begin(const DB::Specs::Interval& spec) const {
  return m_key_end.empty() ||
         spec.is_matching_begin(m_cells.key_seq, m_key_end);
}

SWC_CAN_INLINE
bool Block::includes_end(const DB::Specs::Interval& spec) const {
  return m_prev_key_end.empty() ||
         spec.is_in_previous(m_cells.key_seq, m_prev_key_end);
}

SWC_CAN_INLINE
void Block::preload() {
  Env::Rgr::post([this](){
    scan(ReqScanBlockLoader::Ptr(
      new ReqScanBlockLoader(blocks->range->cfg->block_size())
    ));
  });
}

SWC_CAN_INLINE
bool Block::add_logged(const DB::Cells::Cell& cell) {
  if(!is_in_end(cell.key))
    return false;

  if(loaded()) {
    Core::ScopedLock lock(m_mutex);
    ssize_t sz = m_cells.size_of_internal();
    m_cells.add_raw(cell);
    Env::Rgr::res().adj_mem_usage(ssize_t(m_cells.size_of_internal()) - sz);
    splitter();
  }
  return true;
}

SWC_CAN_INLINE
void Block::load_final(const DB::Cells::MutableVec& vec_cells) {
  if(vec_cells.empty()) {
    Core::MutexSptd::scope lock(m_mutex_state);
    m_state.store(State::LOADED);

  } else {
    ssize_t sz;
    {
      Core::ScopedLock lock(m_mutex);
      sz = m_cells.size_of_internal();
      for(auto cells : vec_cells) {
        if(!cells->scan_after(m_prev_key_end, m_key_end, m_cells))
          break;
        splitter();
      }
      {
        Core::MutexSptd::scope lock(m_mutex_state);
        m_state.store(State::LOADED);
      }
      sz = ssize_t(m_cells.size_of_internal()) - sz;
    }
    Env::Rgr::res().adj_mem_usage(sz);
  }
}

SWC_CAN_INLINE
size_t Block::load_cells(const uint8_t* buf, size_t remain,
                         uint32_t revs, size_t avail,
                         bool& was_splitted, bool synced) {
  size_t count = 0;
  size_t added = 0;
  size_t offset_hint = 0;

  Core::ScopedLock lock(m_mutex);
  if(revs > blocks->range->cfg->cell_versions())
    // schema change from more to less results in dups
    synced = false;
  else if(!synced && m_cells.empty())
    synced = true;
  ssize_t sz = m_cells.size_of_internal();

  try { for(DB::Cells::Cell cell; remain; ++count) {

    cell.read(&buf, &remain);

    if(!m_prev_key_end.empty() &&
        DB::KeySeq::compare(m_cells.key_seq, m_prev_key_end, cell.key)
          != Condition::GT)
      continue;

    if(!m_key_end.empty() &&
        DB::KeySeq::compare(m_cells.key_seq, m_key_end, cell.key)
          == Condition::GT)
      break;

    if(cell.has_expired(m_cells.ttl))
      continue;

    synced
      ? m_cells.add_sorted(cell)
      : m_cells.add_raw(cell, &offset_hint);

    if(!(++added % 1000)) {
      Env::Rgr::res().adj_mem_usage(ssize_t(m_cells.size_of_internal()) - sz);
      if(splitter()) {
        was_splitted = true;
        offset_hint = 0;
      }
      sz = m_cells.size_of_internal();
    }

  } } catch(...) {
    const Error::Exception& e = SWC_CURRENT_EXCEPTION("");
    SWC_LOG_OUT(LOG_ERROR,
      SWC_LOG_OSTREAM << "Cell trunclated at count="
        << count << '/' << avail << " remain=" << remain;
      m_prev_key_end.print(SWC_LOG_OSTREAM << ' ');
      m_key_end.print(SWC_LOG_OSTREAM << " < key <= ");
      e.print(SWC_LOG_OSTREAM << ' ');
    );
  }
  Env::Rgr::res().adj_mem_usage(ssize_t(m_cells.size_of_internal()) - sz);
  return added;
}

SWC_CAN_INLINE
bool Block::splitter() {
  return _need_split() && blocks->_split(ptr(), false);
}

Block::ScanState Block::scan(const ReqScan::Ptr& req) {
  {
    State at(State::NONE);
    Core::MutexSptd::scope lock(m_mutex_state);
    m_state.compare_exchange_weak(at, State::LOADING);
    switch(at) {
      case State::NONE: {
        m_loader = new BlockLoader(ptr());
        m_loader->add(req);
        break;
      }
      case State::LOADING: {
        m_loader->add(req);
        return ScanState::QUEUED;
      }
      case State::LOADED: {
        goto proceed;
      }
    }
  }
  m_loader->run();
  return ScanState::QUEUED;

  proceed: switch(req->type) {
    case ReqScan::Type::BLK_PRELOAD: {
      processing_decrement();
      return ScanState::RESPONDED;
    }
    default:
      return _scan(req, true);
  }
}

void Block::loader_loaded() {
  do {
    auto& q = m_loader->q_req.front();
    switch(q.req->type) {
      case ReqScan::Type::BLK_PRELOAD: {
        processing_decrement();
        break;
      }
      default: {
        if(!m_loader->error) {
          q.req->profile.add_block_load(
            q.ts, m_loader->count_cs_blocks, m_loader->count_fragments);
          Env::Rgr::post([this, req=q.req]() { _scan(req); } );
          break;
        }
        blocks->processing_decrement();
        processing_decrement();
        int err = m_loader->error;
        q.req->response(err);
      }
    }
    m_loader->q_req.pop();
  } while(!m_loader->q_req.empty());

  Core::MutexSptd::scope lock(m_mutex_state);
  delete m_loader;
  m_loader = nullptr;
}

Block::Ptr Block::split(bool loaded) {
  Block::Ptr blk = nullptr;
  if(m_mutex.try_lock()) {
    blk = _split(loaded);
    m_mutex.unlock();
  }
  return blk;
}

Block::Ptr Block::_split(bool loaded) {
  Block::Ptr blk = Block::make(
    DB::Cells::Interval(m_cells.key_seq),
    blocks,
    loaded ? State::LOADED : State::NONE
  );
  ssize_t sz = loaded ? 0 : m_cells.size_of_internal();
  if(!m_cells.split(blk->m_cells, loaded)) {
    delete blk;
    return nullptr;
  }
  {
    Core::MutexAtomic::scope lock(m_mutex_intval);
    blk->m_key_end.copy(m_key_end);
    m_key_end.copy(m_cells.back().key);
  }
  if(sz)
    Env::Rgr::res().adj_mem_usage(ssize_t(m_cells.size_of_internal()) - sz);

  _add(blk);
  return blk;
}

SWC_CAN_INLINE
void Block::_add(Block::Ptr blk) {
  blk->prev = ptr();
  if(next) {
    blk->next = next;
    next->prev = blk;
  }
  get_key_end(blk->m_prev_key_end);
  next = blk;
}

size_t Block::release() {
  size_t released = 0;
  if(!m_processing && loaded() && m_mutex.try_lock()) {
    bool support;
    if(!m_processing && loaded() && m_mutex_state.try_full_lock(support)) {
      auto at(State::LOADED);
      if(!m_loader && !m_processing &&
         m_state.compare_exchange_weak(at, State::NONE)) {
        released += m_cells.size_of_internal();
        m_cells.free();
      }
      m_mutex_state.unlock(support);
    }
    m_mutex.unlock();
  }
  if(released)
    Env::Rgr::res().less_mem_usage(released);
  return released;
}

SWC_CAN_INLINE
void Block::processing_increment() noexcept {
  m_processing.fetch_add(1);
}

SWC_CAN_INLINE
void Block::processing_decrement() noexcept {
  m_processing.fetch_sub(1);
}

SWC_CAN_INLINE
bool Block::loaded() const noexcept {
  return m_state == State::LOADED;
}

SWC_CAN_INLINE
bool Block::need_load() const noexcept {
  return m_state == State::NONE;
}

SWC_CAN_INLINE
bool Block::processing() noexcept {
  bool busy = m_processing ||
              m_state == State::LOADING ||
              !m_mutex.try_lock();
  if(!busy) {
    bool support;
    busy = m_processing ||
           m_state == State::LOADING ||
           !m_mutex_state.try_full_lock(support);
    if(!busy) {
      busy = m_processing ||
             m_state == State::LOADING ||
             m_loader;
      m_mutex_state.unlock(support);
    }
    m_mutex.unlock();
  }
  return busy;
}

SWC_CAN_INLINE
size_t Block::size() {
  Core::SharedLock lock(m_mutex);
  return _size();
}

SWC_CAN_INLINE
size_t Block::_size() const noexcept {
  return m_cells.size();
}

SWC_CAN_INLINE
size_t Block::size_bytes() {
  Core::SharedLock lock(m_mutex);
  return m_cells.size_bytes();
}

SWC_CAN_INLINE
size_t Block::size_of_internal() {
  Core::SharedLock lock(m_mutex);
  return m_cells.size_of_internal();
}

SWC_CAN_INLINE
bool Block::_need_split() const noexcept {
  auto sz = _size();
  return sz > 1 &&
    (sz >= blocks->range->cfg->block_cells() * 2 ||
     m_cells.size_bytes() >= blocks->range->cfg->block_size() * 2) &&
    !m_cells.has_one_key();
}

void Block::print(std::ostream& out) {
  out << "Block(state=" <<  int(m_state.load())
      << ' ' << DB::Types::to_string(m_cells.key_seq)
      << ' ' << m_prev_key_end << " < key <= ";
  {
    Core::MutexAtomic::scope lock(m_mutex_intval);
    out << m_key_end;
  }

  out << ' ';
  if(m_mutex.try_lock()) {
    m_cells.print(out);
    m_mutex.unlock();
  } else {
    out << "CellsLocked";
  }
  out << " processing=" << m_processing.load() << ')';
}

Block::ScanState Block::_scan(const ReqScan::Ptr& req, bool synced) {
  // if(is_next(req->spec)) // ?has-changed(split)
  int err = Error::OK;
  uint64_t ts = Time::now_ns();
  try {
    Core::SharedLock lock(m_mutex);
    m_cells.scan(req.get());

  } catch (...) {
    const Error::Exception& e = SWC_CURRENT_EXCEPTION("");
    SWC_LOG_OUT(LOG_ERROR, SWC_LOG_OSTREAM << e; );
    err = e.code();
  }
  req->profile.add_block_scan(ts);

  processing_decrement();

  if(err || req->reached_limits()) {
    if(req->with_block())
      req->block = ptr();
    blocks->processing_decrement();
    req->response(err);
    return ScanState::RESPONDED;
  }

  if(req->release_block)
    release();

  if(!synced)
    blocks->scan(req, ptr());

  return ScanState::SYNCED;
}



}}
