/*
 * Copyright (C) 2019 SWC-DB (author: Kashirin Alex (kashirin.alex@gmail.com))
 */


#ifndef swcdb_lib_db_Files_RangeBlocks_h
#define swcdb_lib_db_Files_RangeBlocks_h

#include "swcdb/db/Cells/ReqScan.h"

namespace SWC { namespace Files { namespace Range {
//Forawrd Declaration
class Blocks;
}}}

#include "swcdb/db/Files/RangeBlock.h"

#include "swcdb/db/Files/CellStoreReaders.h"
#include "swcdb/db/Files/CommitLog.h"
#include "swcdb/db/Files/RangeData.h"

namespace SWC { namespace Files { namespace Range {


class Blocks final {
  public:
  typedef Blocks* Ptr;

  // scan >> blk match >> load-cs + load+logs 

  DB::RangeBase::Ptr    range;
  CommitLog::Fragments  commitlog;
  CellStore::Readers    cellstores;

  explicit Blocks() : m_block(nullptr), m_processing(0) { }
  
  void init(DB::RangeBase::Ptr for_range) {
    range = for_range;
    commitlog.init(range);
    cellstores.init(range);
  }

  Ptr ptr() {
    return this;
  }

  ~Blocks() {  }
  
  void processing_increment() {
    m_processing++;
  }

  void processing_decrement() {
    m_processing--;
  }

  void load(int& err) {
    commitlog.load(err);
    cellstores.load(err);
  }

  void unload() {
    wait_processing();
    commitlog.commit_new_fragment(true);  
    std::scoped_lock lock(m_mutex);
    
    commitlog.unload();
    cellstores.unload();  
    _clear();
    range = nullptr;
  }
  
  void remove(int& err) {
    wait_processing();
    std::scoped_lock lock(m_mutex);

    commitlog.remove(err);
    cellstores.remove(err);   
    _clear();
    range = nullptr;
  }
  
  void apply_new(int &err,
                CellStore::Writers& w_cellstores, 
                std::vector<CommitLog::Fragment::Ptr>& fragments_old) {
    wait_processing();
    std::scoped_lock lock(m_mutex);

    cellstores.replace(err, w_cellstores);
    if(err)
      return;
    RangeData::save(err, cellstores);
      
    commitlog.remove(err, fragments_old);
  }

  const bool need_split(uint32_t sz) const {
    return sz >= range->cfg->block_cells() * 2;
  }

  void add_logged(const DB::Cells::Cell& cell) {
    processing_increment();

    commitlog.add(cell);
    
    bool to_split=false;
    Block::Ptr blk;
    {
      std::shared_lock lock(m_mutex);
      for(blk=m_block; blk; blk=blk->next) {
        if(blk->add_logged(cell)) {
          to_split = blk->loaded();
          break;
        }
      }
    }
    if(to_split)
      split(blk, true);

    processing_decrement();
  }

  void scan(DB::Cells::ReqScan::Ptr req, Block::Ptr blk_ptr = nullptr) {
    if(!blk_ptr)
      processing_increment();

    if(req->expired()) {
      processing_decrement();
      return;
    }    

    int err = Error::OK;
    {
      std::scoped_lock lock(m_mutex);
      if(!m_block) 
        init_blocks(err);
    }
    if(err) {
      processing_decrement();
      req->response(err);
      return;
    }
    for(Block::Ptr eval, nxt_blk, blk=nxt_blk=nullptr; ;
        blk = nullptr, nxt_blk = nullptr) {
      {
        std::shared_lock lock(m_mutex);
        for(eval=blk_ptr? blk_ptr->next : m_block; eval; eval=eval->next) {
          if(eval->removed() || !eval->is_next(req->spec)) 
            continue;
          blk = eval;
          blk_ptr = blk;
          blk->processing_increment();

          if((!req->spec.flags.limit || req->spec.flags.limit > 1) 
              && eval->next 
              && !Env::Resources.need_ram(range->cfg->block_size() * 10)
              && !eval->next->loaded() && !eval->next->removed()) {
            nxt_blk = eval->next;
            nxt_blk->processing_increment();
          }
          break;
        }
      }
      if(blk == nullptr)
        break;
      
      if(nxt_blk != nullptr) {
        if(nxt_blk->includes(req->spec))
          nxt_blk->preload();
        else 
          nxt_blk->processing_decrement();
      }

      if(Env::Resources.need_ram(range->cfg->block_size())) {
        asio::post(*Env::IoCtx::io()->ptr(), 
          [blk, ptr=ptr()](){
            ptr->release_prior(blk); // release_and_merge(blk);
          }
        );
      }

      if(blk->scan(req)) // true (queued || responded)
        return;
    }

    processing_decrement();

    req->response(err);
  }

  void split(Block::Ptr blk, bool loaded=true) {
    if(need_split(blk->size()) && m_mutex.try_lock()) {
      do blk = blk->split(loaded);
      while(need_split(blk->size()));
      m_mutex.unlock();
    }
  }

  const bool _split(Block::Ptr blk, bool loaded=true) {
    // blk is under lock
    if(need_split(blk->_size()) && m_mutex.try_lock()) {
      do blk = blk->_split(loaded);
      while(need_split(blk->_size()));
      m_mutex.unlock();
      return true;
    }
    return false;
  }

  const size_t cells_count() {
    size_t sz = 0;
    std::shared_lock lock(m_mutex);
    for(Block::Ptr blk=m_block; blk; blk=blk->next)
      sz += blk->size();
    return sz;
  }

  const size_t size() {
    std::shared_lock lock(m_mutex);
    return _size();
  }

  const size_t size_bytes() {
    std::shared_lock lock(m_mutex);
    return _size_bytes();
  }

  const size_t size_bytes_total(bool only_loaded=false) {
    std::shared_lock lock(m_mutex);
    return _size_bytes() 
          + cellstores.size_bytes(only_loaded) 
          + commitlog.size_bytes(only_loaded);
  }

  void release_prior(Block::Ptr ptr) {
    std::shared_lock lock(m_mutex);
    if(ptr->prev)
      ptr->prev->release();
  }

  /*
  void release_and_merge(Block::Ptr ptr) {
    std::scoped_lock lock(m_mutex);
    bool state = false;
    for(size_t idx = 0; idx<m_blocks.size(); idx++) {
      if(ptr == m_blocks[idx]) {
        if(idx < 2)
          return;
        auto ptr1 = m_blocks[idx-2];
        if(ptr1->processing())
          return;
        auto ptr2 = m_blocks[idx-1];
        if(ptr2->processing())
          return;
        ptr2->merge_and_release(ptr1);
        delete ptr1;
        m_blocks.erase(m_blocks.begin()+idx-2);
        --idx;
        //state = true;
      }
    }
    if(state) {
      for(auto blk : m_blocks)
        std::cout << " " << blk->to_string() << "\n"; 
    }
  }
  */

  const size_t release(size_t bytes=0) {
    size_t released = cellstores.release(bytes);
    if(!bytes || released < bytes) {

      released += commitlog.release(bytes ? bytes-released : bytes);
      if(!bytes || released < bytes) {

        std::shared_lock lock(m_mutex);
        for(Block::Ptr blk=m_block; blk; blk=blk->next) {
          released += blk->release();
          if(bytes && released >= bytes)
            break;
        }
      }
    }
    if(!bytes && !processing()) {
      std::scoped_lock lock(m_mutex);
      _clear();
      bytes = 0;
    }
    //else if(_size() > 1000)
    // merge in pairs down to 1000 blks
    
    return released;
  }

  const bool processing() {
    std::shared_lock lock(m_mutex);
    return _processing();
  }

  void wait_processing() {
    while(processing() || commitlog.processing() || cellstores.processing())
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  const std::string to_string(){
    std::scoped_lock lock(m_mutex);

    std::string s("Range::Blocks(count=");
    s.append(std::to_string(_size()));

    s.append(" blocks=[");
    
    for(Block::Ptr blk = m_block; blk; blk=blk->next) {
      s.append(blk->to_string());
      s.append(", ");
    }
    s.append("] ");

    s.append(commitlog.to_string());

    s.append(" ");
    s.append(cellstores.to_string());

    s.append(" processing=");
    s.append(std::to_string(_processing()));

    s.append(" bytes=");
    s.append(std::to_string(_size_bytes()));

    s.append(")");
    return s;
  } 

  private:

  const size_t _size() {
    size_t sz = 0;
    for(Block::Ptr blk=m_block; blk; blk=blk->next)
      sz++;
    return sz;
  }

  const size_t _size_bytes() {
    size_t sz = 0;
    for(Block::Ptr blk=m_block; blk; blk=blk->next)
      sz += blk->size_bytes();
    return sz;
  }
  
  const bool _processing() const {
    if(m_processing)
      return true;
    for(Block::Ptr blk=m_block; blk; blk=blk->next) {
      if(blk->processing()) 
        return true;
    }
    return false;
  }

  void _clear() {
    Block::Ptr blk = m_block;
    for(; blk; blk=blk->next) {
      if(blk->prev)
        delete blk->prev;
      if(!blk->next) {
        delete blk;
        break;
      }
    }
    m_block = nullptr;
  }

  void init_blocks(int& err) {
    std::vector<CellStore::Block::Read::Ptr> blocks;
    cellstores.get_blocks(err, blocks);
    if(err) {
      _clear();
      return;
    }

    Block::Ptr blk = nullptr;
    Block::Ptr new_blk;
    for(auto cs_blk : blocks) {
      new_blk = Block::make(cs_blk->interval, ptr());
      if(blk == nullptr)
        m_block = new_blk;
      else
        blk->add(new_blk);
      blk = new_blk;
    }
    if(!m_block) {
      err = Error::RS_NOT_LOADED_RANGE;
      return;
    }

    if(range->is_any_begin())
      m_block->free_key_begin();
    if(range->is_any_end()) 
      blk->free_key_end();

  }

  std::shared_mutex   m_mutex;
  Block::Ptr          m_block;
  std::atomic<size_t> m_processing;

};





}}}



//#ifdef SWC_IMPL_SOURCE
#include "../../../../lib/swcdb/db/Files/RangeBlock.cc"
//#endif 

#endif