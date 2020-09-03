/*
 * Copyright Since 2019 SWC-DB© [author: Kashirin Alex kashirin.alex@gmail.com]
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */


#include "swcdb/db/Protocol/Mngr/req/RangeCreate.h"
#include "swcdb/db/Protocol/Mngr/req/RangeUnloaded.h"
#include "swcdb/db/Protocol/Mngr/req/RangeRemove.h"

#include "swcdb/ranger/db/CommitLogCompact.h"
#include "swcdb/ranger/db/CommitLogSplitter.h"

namespace SWC { namespace Ranger {
  
struct CompactRange::InBlock {

  InBlock(const Types::KeySeq key_seq, size_t size, InBlock* inblock = nullptr)
          : has_last(inblock != nullptr), 
            cells(size + 1000000), header(key_seq), err(Error::OK),
            last_cell(0) {
    if(has_last)
      inblock->move_last(this);
  }

  InBlock(const InBlock&) = delete;

  InBlock(const InBlock&&) = delete;
  
  InBlock& operator=(const InBlock&) = delete;

  ~InBlock() { }

  size_t cell_avg_size() const {
    return cells.fill()/header.cells_count;
  }

  void add(const DB::Cells::Cell& cell) {
    ++header.cells_count;
    cells.set_mark(); // start of last cell
    cell.write(cells);
    last_cell = cells.mark;
  }

  void set_offset(DB::Specs::Interval& spec) const {
    DB::Cells::Cell cell;
    const uint8_t* ptr = last_cell;
    size_t remain = cells.ptr - ptr;
    cell.read(&ptr, &remain); 
    spec.offset_key.copy(cell.key);
    spec.offset_rev = cell.timestamp;
  }

  void move_last(InBlock* to) {
    const uint8_t* ptr = last_cell;
    size_t remain = cells.ptr - ptr;
    
    DB::Cells::Cell cell;
    cell.read(&ptr, &remain); 
    to->add(cell);

    --header.cells_count;
    cells.ptr = (uint8_t*)last_cell;
    cells.mark = 0;
  }

  void finalize_interval(bool any_begin, bool any_end) {    
    const uint8_t* ptr = cells.base;
    size_t remain = cells.fill();
    bool set_begin = true;

    DB::Cells::Cell cell;
    while(remain) {
      cell.read(&ptr, &remain); 
      header.interval.align(cell.key);
      header.interval.expand(cell.timestamp);
      
      if(set_begin) {
        header.interval.expand_begin(cell);
        set_begin = false;
      }
    }
    header.interval.expand_end(cell);

    if(any_begin)
      header.is_any |= CellStore::Block::Header::ANY_BEGIN;
    if(any_end)
      header.is_any |= CellStore::Block::Header::ANY_END;
  }

  void finalize_encode(Types::Encoding encoding) {
    header.encoder = encoding;
    DynamicBuffer output;
    CellStore::Block::Write::encode(err, cells, output, header);
    if(err)
      return;
    cells.free();
    cells.take_ownership(output);
  }

  const uint8_t             has_last;
  DynamicBuffer             cells;
  CellStore::Block::Header  header;

  int                  err;

  private:

  const uint8_t*       last_cell;
};


CompactRange::CompactRange(Compaction::Ptr compactor, const RangePtr& range,
                           const uint32_t cs_size, const uint32_t blk_size) 
            : ReqScan(ReqScan::Type::COMPACTION, true, 
                      compactor->cfg_read_ahead->get()/2), 
              compactor(compactor), range(range),
              cs_size(cs_size), blk_size(blk_size), 
              blk_cells(range->cfg->block_cells()), 
              blk_encoding(range->cfg->block_enc()),
              m_inblock(new InBlock(range->cfg->key_seq, blk_size)),
              state_default(range->blocks.cellstores.blocks_count() > 1 
                ? Range::COMPACT_COMPACTING : Range::COMPACT_PREPARING),
              req_last_time(0),
              m_getting(true), m_log_sz(0),
              m_chk_timer(
                asio::high_resolution_timer(*Env::IoCtx::io()->ptr())) {
  spec.flags.max_versions = range->cfg->cell_versions();
}

CompactRange::~CompactRange() { 
  if(m_inblock)
    delete m_inblock;
    
  if(!m_q_intval.empty()) do {
    if(m_q_intval.front()) delete m_q_intval.front();
  } while(m_q_intval.pop_and_more());

  if(!m_q_encode.empty()) do {
    if(m_q_encode.front()) delete m_q_encode.front();
  } while(m_q_encode.pop_and_more());

  if(!m_q_write.empty()) do {
    if(m_q_write.front()) delete m_q_write.front();
  } while(m_q_write.pop_and_more());
}

SWC_SHOULD_INLINE
CompactRange::Ptr CompactRange::shared() {
  return std::dynamic_pointer_cast<CompactRange>(shared_from_this());
}

void CompactRange::initialize() {
  range->compacting(Range::COMPACT_APPLYING);
  range->blocks.wait_processing(); // sync processing state

  if(range->blocks.commitlog.cells_count(true))
    range->blocks.commitlog.commit_new_fragment(true);

  initial_commitlog(1);
}

void CompactRange::initial_commitlog(int tnum) {
  auto ptr = shared();
  m_log_sz = range->blocks.commitlog.size();
  if(m_log_sz < CommitLog::Fragments::MIN_COMPACT)
    return initial_commitlog_done(ptr, nullptr);

  std::vector<CommitLog::Fragments::Vec> groups;
  size_t need = range->blocks.commitlog.need_compact(
    groups, {}, CommitLog::Fragments::MIN_COMPACT);
  if(need) {
    new CommitLog::Compact(
      &range->blocks.commitlog, tnum, groups,
      [ptr] (const CommitLog::Compact* compact) {
        ptr->initial_commitlog_done(ptr, compact); 
      }
    );
  } else {
    initial_commitlog_done(ptr, nullptr);
  } 
}

void CompactRange::initial_commitlog_done(CompactRange::Ptr ptr, 
                                          const CommitLog::Compact* compact) {
  if(m_stopped) {
    if(compact) 
      delete compact;
    return quit();
  }
  if(compact) {
    int tnum = 0;
    if(compact->nfrags > 100 ||
       compact->ngroups > CommitLog::Fragments::MIN_COMPACT ||
       compact->nfrags / compact->ngroups > CommitLog::Fragments::MIN_COMPACT)
      tnum += compact->repetition + 1;
    delete compact;
    if(tnum) {
      range->compacting(Range::COMPACT_PREPARING); // range scan can continue
      return initial_commitlog(tnum);
    }
  }

  range->blocks.commitlog.get(fragments_old); // fragments for removal

  range->blocks.cellstores.get_key_end(m_required_key_last);
  for(auto& frag : fragments_old) {
    if(DB::KeySeq::compare(range->cfg->key_seq, 
        m_required_key_last, frag->interval.key_end) == Condition::GT)
    m_required_key_last.copy(frag->interval.key_end);
  }
  SWC_LOGF(LOG_INFO,
    "COMPACT-PROGRESS %lu/%lu early-split possible from scan offset %s",
      range->cfg->cid, range->rid, m_required_key_last.to_string().c_str()
  );

  range->compacting(state_default); // range scan &/ add can continue
  req_ts = Time::now_ns();
  progress_check_timer();

  range->scan_internal(ptr);
}

bool CompactRange::with_block() {
  return true;
}

bool CompactRange::selector(const Types::KeySeq key_seq, 
                            const DB::Cells::Cell& cell, bool&) {
  return spec.is_matching(
    key_seq, cell.key, cell.timestamp, cell.control & DB::Cells::TS_DESC)
    &&
    (spec.key_start.empty() ||
      DB::KeySeq::is_matching(key_seq, spec.key_start, cell.key))
    ;
}

bool CompactRange::reached_limits() {
  return m_stopped 
      || (m_inblock->header.cells_count > 1 && 
          m_inblock->cells.fill() + m_inblock->cell_avg_size() >= blk_size)
      || m_inblock->header.cells_count >= blk_cells + 1;
}

bool CompactRange::add_cell_and_more(const DB::Cells::Cell& cell) {
  auto sz = m_inblock->cells.fill();
  m_inblock->add(cell);
  profile.add_cell(m_inblock->cells.fill() - sz);
  return !reached_limits();
}

void CompactRange::response(int& err) {
  if(m_stopped)
    return;

  total_cells = profile.cells_count;
  ++total_blocks;
  req_last_time = Time::now_ns() - req_ts;
  req_ts = Time::now_ns();

  profile.finished();
  SWC_LOGF(LOG_INFO, 
    "COMPACT-PROGRESS %lu/%lu blocks=%lu avg(i=%ld e=%ld w=%ld)us %s err=%d",
    range->cfg->cid, range->rid,
    total_blocks.load(), 
    (time_intval / total_blocks)/1000, 
    (time_encode / total_blocks)/1000, 
    (time_write / total_blocks)/1000, 
    profile.to_string().c_str(), err
  );

  bool finishing;
  if((finishing = !reached_limits())) {
    stop_check_timer();
    range->compacting(state_default = Range::COMPACT_APPLYING);
    range->blocks.wait_processing();
    range->blocks.commitlog.commit_new_fragment(true);
  }

  auto in_block = m_inblock->header.cells_count <= 1 ? nullptr : m_inblock;
  if(in_block) {
    m_inblock = new InBlock(range->cfg->key_seq, blk_size, in_block);
    m_inblock->set_offset(spec);

    if(can_split_at() > 0 && DB::KeySeq::compare(range->cfg->key_seq, 
        m_required_key_last, spec.offset_key) == Condition::GT) {
      spec.key_start.set(spec.offset_key, Condition::EQ);
      spec.range_end.copy(spec.offset_key);

      SWC_LOGF(LOG_INFO,
        "COMPACT-PROGRESS %lu/%lu finishing early-split scan offset %s",
        range->cfg->cid, range->rid, spec.offset_key.to_string().c_str()
      );
    }
  }

  if(m_q_intval.push_and_is_1st(in_block))
    RangerEnv::maintenance_post([ptr=shared()](){ ptr->process_interval(); });

  if(m_stopped || !in_block)
    return;

  finishing
    ? commitlog_done(nullptr)
    : commitlog(1);
}

bool CompactRange::is_slow_req(int64_t& median) const {
  median = (total_cells
    ? (Time::now_ns() - profile.ts_start) / total_cells : 10000) 
    * blk_cells * 3;
  return req_last_time > median || Time::now_ns() - req_ts > median;
}

void CompactRange::commitlog(int tnum) {
  size_t log_sz = range->blocks.commitlog.size();
  if((log_sz > m_log_sz ? log_sz - m_log_sz : m_log_sz - log_sz)
      < CommitLog::Fragments::MIN_COMPACT)
    return commitlog_done(nullptr);

  std::vector<CommitLog::Fragments::Vec> groups;
  size_t need = range->blocks.commitlog.need_compact(
    groups, fragments_old, CommitLog::Fragments::MIN_COMPACT);
  if(need) {
    new CommitLog::Compact(
      &range->blocks.commitlog, tnum, groups,
      [ptr=shared()] (const CommitLog::Compact* compact) {
        ptr->commitlog_done(compact); 
      }
    );
  } else {
    m_log_sz = log_sz;
    commitlog_done(nullptr);
  }
}

void CompactRange::commitlog_done(const CommitLog::Compact* compact) {
  if(m_stopped) {
    if(compact)
      delete compact;
    return;
  }
  if(compact) {
    int tnum = 0;
    if(compact->nfrags > 100 ||
       compact->ngroups > range->cfg->log_rollout_ratio() ||
       compact->nfrags / compact->ngroups > range->cfg->log_rollout_ratio())
      tnum += compact->repetition + 1;
    delete compact;

    int64_t median;
    range->compacting(tnum && is_slow_req(median)
      ? Range::COMPACT_PREPARING : state_default.load() );
    if(tnum && !m_stopped && !m_chk_final && range->is_loaded())
      return commitlog(tnum);
  }
  {
    Mutex::scope lock(m_mutex);
    m_getting = false;
  }
  request_more();
}

void CompactRange::progress_check_timer() {
  if(m_stopped || m_chk_final)
    return;

  int64_t median;
  bool slow = is_slow_req(median);
  if(!range->compacting_is(Range::COMPACT_APPLYING)) {
    range->compacting(slow? Range::COMPACT_PREPARING : state_default.load());
    request_more();
  }

  if((median /= 1000000) < 1000)
    median = 1000;
  Mutex::scope lock(m_mutex);
  m_chk_timer.expires_from_now(std::chrono::milliseconds(median));
  m_chk_timer.async_wait(
    [ptr=shared()](const asio::error_code& ec) {
      if(ec == asio::error::operation_aborted)
        return;
      ptr->progress_check_timer();
    }
  );
}

void CompactRange::stop_check_timer() {
  if(!m_chk_final) {
    m_chk_final = true;
    Mutex::scope lock(m_mutex);
    m_chk_timer.cancel();
  }
}

void CompactRange::request_more() {
  if(m_stopped)
    return;
  {
    Mutex::scope lock(m_mutex);
    if(m_getting)
      return;
    size_t sz = m_q_write.size() + m_q_intval.size() + m_q_encode.size();
    if(sz && (sz >= compactor->cfg_read_ahead->get() ||
             (sz > RangerEnv::res().avail_ram()/blk_size &&
              range->blocks.release(sz * blk_size) < sz * blk_size)))
      return;
    m_getting = true;
  }

  RangerEnv::maintenance_post(
    [ptr=shared()](){ ptr->range->scan_internal(ptr->get_req_scan()); });
}

void CompactRange::process_interval() {
  auto start = Time::now_ns();
  InBlock* in_block;
  do {
    if(m_stopped) 
      return;
    if((in_block = m_q_intval.front())) {
      request_more();
      in_block->finalize_interval(false, false);
    }
    if(m_q_encode.push_and_is_1st(in_block))
      RangerEnv::maintenance_post([ptr=shared()](){ ptr->process_encode(); });
  } while(m_q_intval.pop_and_more() && !m_stopped);
  time_intval += Time::now_ns() - start;
  request_more();
}

void CompactRange::process_encode() {
  auto start = Time::now_ns();
  InBlock* in_block;
  do {
    if(m_stopped) 
      return;
    if((in_block = m_q_encode.front())) {
      request_more();
      in_block->finalize_encode(blk_encoding);
    }
    if(m_q_write.push_and_is_1st(in_block))
      RangerEnv::maintenance_post([ptr=shared()](){ ptr->process_write(); });
  } while(m_q_encode.pop_and_more() && !m_stopped);
  time_encode += Time::now_ns() - start;
  request_more();
}

void CompactRange::process_write() {
  auto start = Time::now_ns();
  int err = Error::OK;
  InBlock* in_block;
  do {
    if(m_stopped)
      return;

    if(!(in_block = m_q_write.front())) {
      time_write += Time::now_ns() - start;
      return finalize();
    }

    if(in_block->err)
      return quit();

    request_more();

    write_cells(err, in_block);

    if(m_stopped)
      return;
    if(err || !range->is_loaded() || compactor->stopped())
      return quit();

    delete in_block;
  } while(m_q_write.pop_and_more() && !m_stopped);

  time_write += Time::now_ns() - start;
  request_more();
}

csid_t CompactRange::create_cs(int& err) { 
  if(!tmp_dir) { 
    Env::FsInterface::interface()->rmdir(
      err, range->get_path(Range::CELLSTORES_TMP_DIR));
    err = Error::OK;
    Env::FsInterface::interface()->mkdirs(
      err, range->get_path(Range::CELLSTORES_TMP_DIR));
    tmp_dir = true;
    if(err)
      return 0;
  }

  csid_t csid = 1;
  {
    Mutex::scope lock(m_mutex);
    csid += cellstores.size();
  }
  cs_writer = std::make_shared<CellStore::Write>(
    csid, 
    range->get_path_cs_on(Range::CELLSTORES_TMP_DIR, csid), 
    range, 
    spec.flags.max_versions
  );
  cs_writer->create(err, -1, range->cfg->file_replication(), blk_size);

  uint32_t portion = range->cfg->compact_percent()/10;
  if(!portion) portion = 1;
  if(csid == range->cfg->cellstore_max() * portion) {
    stop_check_timer();
    // mitigate add req. total workload
    range->compacting(state_default = Range::COMPACT_PREPARING);
  }
  return csid;

}

void CompactRange::write_cells(int& err, InBlock* in_block) {
  if(cs_writer == nullptr) {
    if(create_cs(err) == 1 && range->is_any_begin())
      in_block->header.is_any |= CellStore::Block::Header::ANY_BEGIN;
    if(err)
      return;
  }

  cs_writer->block_write(err, in_block->cells, in_block->header);
  if(err)
    return;

  if(cs_writer->size >= cs_size) {
    add_cs(err);
    if(err)
      return;
  }
}

void CompactRange::add_cs(int& err) {
  {
    Mutex::scope lock(m_mutex);
    if(cellstores.empty())
      cs_writer->prev_key_end.copy(range->prev_range_end);
    else
      cs_writer->prev_key_end.copy(cellstores.back()->interval.key_end);
    cellstores.push_back(cs_writer);
  }
  cs_writer->finalize(err);
  cs_writer = nullptr;
}

ssize_t CompactRange::can_split_at() {
  auto max = range->cfg->cellstore_max();

  Mutex::scope lock(m_mutex);
  if(cellstores.size() < (max < 2 ? 2 : max))
    return 0;

  auto it = cellstores.begin() + 1;
  if((*it)->size < (cs_size/100) * range->cfg->compact_percent())
    return -2;

  size_t at = cellstores.size() / 2;

  split_option: 
    it = cellstores.begin() + at;
    do {
      if(!(*it)->interval.key_begin.equal((*(it-1))->interval.key_end))
        break;
    } while(++it < cellstores.end());

  if(it == cellstores.end()) {
    if(at > 1) {
      at = 1;
      goto split_option;
    }
    return -1;
  }
  return it - cellstores.begin();
}

void CompactRange::finalize() {
  stop_check_timer();
  
  if(!range->is_loaded())
    return quit();

  auto start = Time::now_ns();
  int err = Error::OK;
  bool empty_cs = false;

  if(m_inblock->header.cells_count) {
    // first or/and last block of any-type set with empty-key
    bool any_begin = false;
    if(cs_writer == nullptr) {
      any_begin = create_cs(err) == 1 && range->is_any_begin();
      if(err)
        return quit();
    }
    m_inblock->finalize_interval(any_begin, range->is_any_end());
    cs_writer->block_encode(err, m_inblock->cells, m_inblock->header);
 
  } else if(!cellstores.size() && cs_writer == nullptr) {
    // as an initial empty range cs with range intervals
    empty_cs = true;
    create_cs(err); //csid_t csid = 
    if(err)
      return quit();
    range->get_interval(
      m_inblock->header.interval.key_begin, 
      m_inblock->header.interval.key_end
    );
    if(m_inblock->header.interval.key_begin.empty())
      m_inblock->header.is_any |= CellStore::Block::Header::ANY_BEGIN;
    if(m_inblock->header.interval.key_end.empty())
      m_inblock->header.is_any |= CellStore::Block::Header::ANY_END;
    cs_writer->block_encode(err, m_inblock->cells, m_inblock->header);
  }
  if(err)
    return quit();

  if(cs_writer != nullptr) {
    if(!cs_writer->size)
      return quit();
    add_cs(err);
    if(err)
      return quit();
  }
  time_write += Time::now_ns() - start;

  range->compacting(Range::COMPACT_APPLYING);
  range->blocks.wait_processing();

  ssize_t split_at = can_split_at();
  if(split_at == -1) {
    SWC_LOGF(LOG_WARN,
      "COMPACT-SPLIT %lu/%lu fail(versions-over-cs) cs-count=%lu",
      range->cfg->cid, range->rid, cellstores.size());

  } else if(split_at == -2) {
    SWC_LOGF(LOG_DEBUG,
      "COMPACT-SPLIT %lu/%lu skipping(last-cs-small) cs-count=%lu",
      range->cfg->cid, range->rid, cellstores.size());
  }

  split_at > 0
    ? mngr_create_range(split_at) 
    : apply_new(empty_cs);

}

void CompactRange::mngr_create_range(uint32_t split_at) {
  Protocol::Mngr::Req::RangeCreate::request(
    range->cfg->cid,
    RangerEnv::rgr_data()->rgrid,
    [split_at, cid=range->cfg->cid, ptr=shared()]
    (const client::ConnQueue::ReqBase::Ptr& req, 
     const Protocol::Mngr::Params::RangeCreateRsp& rsp) {
      
      SWC_LOGF(LOG_DEBUG, 
        "Compact::Mngr::Req::RangeCreate err=%d(%s) %lu/%lu", 
        rsp.err, Error::get_text(rsp.err), cid, rsp.rid);

      if(!ptr->m_stopped && rsp.err && 
         rsp.err != Error::COLUMN_NOT_EXISTS &&
         rsp.err != Error::COLUMN_MARKED_REMOVED &&
         rsp.err != Error::COLUMN_NOT_READY) {
        req->request_again();
        return;
      }
      if((!rsp.err || rsp.err == Error::COLUMN_NOT_READY) && rsp.rid)
        ptr->split(rsp.rid, split_at);
      else 
        ptr->apply_new();
    }
  );
}

void CompactRange::mngr_remove_range(const RangePtr& new_range) {
  std::promise<void> res;
  Protocol::Mngr::Req::RangeRemove::request(
    new_range->cfg->cid,
    new_range->rid,
    [new_range, await=&res]
    (const client::ConnQueue::ReqBase::Ptr& req, 
     const Protocol::Mngr::Params::RangeRemoveRsp& rsp) {
      
      SWC_LOGF(LOG_DEBUG, 
        "Compact::Mngr::Req::RangeRemove err=%d(%s) %lu/%lu", 
        rsp.err, Error::get_text(rsp.err), 
        new_range->cfg->cid, new_range->rid);
      
      if(rsp.err && 
         rsp.err != Error::COLUMN_NOT_EXISTS &&
         rsp.err != Error::COLUMN_MARKED_REMOVED &&
         rsp.err != Error::COLUMN_NOT_READY) {
         req->request_again();
      } else {
        await->set_value();
      }
    }
  );
  res.get_future().get();
}

void CompactRange::split(rid_t new_rid, uint32_t split_at) {
  int err = Error::OK;
  Column::Ptr col = RangerEnv::columns()->get_column(err, range->cfg->cid);
  if(col == nullptr || col->removing())
    return quit();

  int64_t ts = Time::now_ns();
  SWC_LOGF(LOG_INFO, "COMPACT-SPLIT %lu/%lu new-rid=%lu", 
           range->cfg->cid, range->rid, new_rid);

  auto new_range = col->get_range(err, new_rid, true);
  if(!err)
    new_range->create_folders(err);
  if(err) {
    SWC_LOGF(LOG_INFO, "COMPACT-SPLIT cancelled err=%d %lu/%lu new-rid=%lu", 
            err, range->cfg->cid, range->rid, new_rid);
    err = Error::OK;
    col->remove(err, new_rid, false);
    mngr_remove_range(new_range);
    return apply_new();
  }
  
  CellStore::Writers new_cellstores;
  auto it = cellstores.begin()+split_at;
  new_cellstores.assign(it, cellstores.end());
  cellstores.erase(it, cellstores.end());

  new_range->create(err, new_cellstores);
  if(!err) 
    range->apply_new(err, cellstores, fragments_old, false);

  if(err) {
    err = Error::OK;
    col->remove(err, new_rid);
    mngr_remove_range(new_range);
    return quit();
  }

  if(range->blocks.commitlog.cells_count()) {
    /* split latest fragments to new_range from new interval key_end */

    fragments_old.clear();
    range->blocks.commitlog.commit_new_fragment(true);
    range->blocks.commitlog.get(fragments_old); // fragments for removal
      
    CommitLog::Splitter splitter(
      cellstores.back()->interval.key_end,
      fragments_old,
      &range->blocks.commitlog,
      &new_range->blocks.commitlog
    );

    splitter.run();
    range->blocks.commitlog.remove(err, fragments_old);

    range->blocks.commitlog.commit_new_fragment(true);
    new_range->blocks.commitlog.commit_new_fragment(true);
  }
  range->expand_and_align(err, true);
  new_range->expand_and_align(err, false);
  //err = Error::OK;

  new_range = nullptr;
  col->unload(
    new_rid, 
    [new_rid, cid=range->cfg->cid, ptr=shared()](int) { 
      Protocol::Mngr::Req::RangeUnloaded::request(
        cid, new_rid,
        [cid, new_rid, ptr]
        (const client::ConnQueue::ReqBase::Ptr& req, 
         const Protocol::Mngr::Params::RangeUnloadedRsp& rsp) {
      
          SWC_LOGF(LOG_DEBUG, 
            "Compact::Mngr::Req::RangeUnloaded err=%d(%s) %lu/%lu", 
            rsp.err, Error::get_text(rsp.err), cid, new_rid);
          if(!ptr->m_stopped && rsp.err && 
             rsp.err != Error::COLUMN_NOT_EXISTS &&
             rsp.err != Error::COLUMN_MARKED_REMOVED &&
             rsp.err != Error::COLUMN_NOT_READY) {
            req->request_again();
          }
        }
      );
    }
  );

  SWC_LOGF(LOG_INFO, "COMPACT-SPLITTED %lu/%lu took=%ldns new-end=%s", 
            range->cfg->cid, range->rid, Time::now_ns() - ts,
            cellstores.back()->interval.key_end.to_string().c_str());
  finished(true);
}

void CompactRange::apply_new(bool clear) {
  int err = Error::OK;
  range->apply_new(err, cellstores, fragments_old, true);
  if(err)
    return quit();

  finished(clear);
}

void CompactRange::completion() {
  m_stopped = true;
  stop_check_timer();

  auto ptr = shared();
  for(int chk = 0; ptr.use_count() > 2; ++chk) { // insure sane
    if(chk == 3000) {
      SWC_LOGF(LOG_INFO, "COMPACT-STOPPING %lu/%lu use_count=%ld", 
                range->cfg->cid, range->rid, ptr.use_count());
      chk = 0;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}

void CompactRange::finished(bool clear) {
  completion();

  SWC_LOGF(LOG_INFO, 
    "COMPACT-FINISHED %lu/%lu cells=%lu blocks=%lu "
    "(total=%ld intval=%ld encode=%ld write=%ld)ms %s",
    range->cfg->cid, range->rid, total_cells.load(), total_blocks.load(),
    (Time::now_ns() - profile.ts_start)/1000000, 
    time_intval/1000000, time_encode/1000000, time_write/1000000,
    profile.to_string().c_str()
  );

  range->compact_require(false);
  compactor->compacted(range, clear);
}

void CompactRange::quit() {
  completion();

  int err = Error::OK;
  if(cs_writer != nullptr) {
    cs_writer->remove(err);
    cs_writer = nullptr;
  }
  if(tmp_dir) {
    tmp_dir = false;
    Env::FsInterface::interface()->rmdir(
      err, range->get_path(Range::CELLSTORES_TMP_DIR));
  }
  SWC_LOGF(LOG_INFO, "COMPACT-ERROR cancelled %lu/%lu", 
           range->cfg->cid, range->rid);

  compactor->compacted(range);
}






}}