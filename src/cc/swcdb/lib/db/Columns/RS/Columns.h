/*
 * Copyright (C) 2019 SWC-DB (author: Kashirin Alex (kashirin.alex@gmail.com))
 */


#ifndef swcdb_lib_db_RS_Columns_Columns_h
#define swcdb_lib_db_RS_Columns_Columns_h

#include "swcdb/lib/fs/Interface.h"
#include "swcdb/lib/db/Columns/Schema.h"

#include "swcdb/lib/core/comm/ResponseCallback.h"
#include "Callbacks.h"
#include "Column.h"

#include <mutex>
#include <memory>
#include <unordered_map>
#include <iostream>

namespace SWC { namespace server { namespace RS {

typedef std::unordered_map<int64_t, ColumnPtr> ColumnsMap;
typedef std::pair<int64_t, ColumnPtr> ColumnsMapPair;



class Columns : public std::enable_shared_from_this<Columns> {

  public:

  enum State{
    OK
  };

  Columns() : m_columns(std::make_shared<ColumnsMap>()), m_state(State::OK) {}

  virtual ~Columns(){}

  ColumnPtr get_column(int &err, int64_t cid, bool initialize){
    ColumnPtr col = nullptr;
    {
      std::lock_guard<std::mutex> lock(m_mutex);

      auto it = m_columns->find(cid);
      if (it != m_columns->end())
        col = it->second;
        
      else if(initialize && !Env::RsData::is_shuttingdown()) {
        col = std::make_shared<Column>(cid);
        m_columns->insert(ColumnsMapPair(cid, col));
      }
    }
    if(initialize) {
      if(Env::RsData::is_shuttingdown())
        err = Error::SERVER_SHUTTING_DOWN;
      else
        col->init(err);
    }
    return col;
  }

  RangePtr get_range(int &err, int64_t cid, int64_t rid,  bool initialize=false){
    ColumnPtr col = get_column(err, cid, initialize);
    if(col == nullptr) 
      return nullptr;
    if(err != Error::OK) 
      return nullptr;
    if(col->removing()) {
      err = Error::COLUMN_MARKED_REMOVED;
      return nullptr;
    }
    return col->get_range(err, rid, initialize);
  }

  void load_range(int &err, int64_t cid, int64_t rid, ResponseCallbackPtr cb){
    if(Env::RsData::is_shuttingdown())
      cb->send_error(Error::SERVER_SHUTTING_DOWN, "");
      
    else if(Env::Schemas::get()->get(cid) == nullptr)
      cb->send_error(Error::COLUMN_SCHEMA_MISSING, "");

    else {
      RangePtr range = get_range(err, cid, rid, true);
      if(Env::RsData::is_shuttingdown())
        cb->send_error(Error::SERVER_SHUTTING_DOWN, "");
      else if(err != Error::OK)
        cb->send_error(err, "");
      else
        range->load(cb);
    }
  }

  void unload_range(int &err, int64_t cid, int64_t rid, Callback::RangeUnloaded_t cb){
    ColumnPtr col = get_column(err, cid, false);
    if(col != nullptr) 
      col->unload(rid, cb);
    
    cb(err);
  }

  void unload_all(int &err){
    std::atomic<int> unloaded = 0;
    {
      std::lock_guard<std::mutex> lock(m_mutex);
      unloaded += m_columns->size();
    }

    std::promise<void>  r_promise;
    Callback::RangeUnloaded_t cb 
      = [&unloaded, await=&r_promise](int err){
        std::cout << "unloaded= " << unloaded.load() << " err=" << err << "\n";
        if(--unloaded == 0)
          await->set_value();
    };

    for(;;){
      std::lock_guard<std::mutex> lock(m_mutex);
      auto it = m_columns->begin();
      if(it == m_columns->end())
        break;
      it->second->unload_all(unloaded, cb);
      m_columns->erase(it);
    }

    if(unloaded > 0)
      r_promise.get_future().wait();
  }

  void remove(int &err, int64_t cid, Callback::ColumnDeleted_t cb){
    ColumnPtr col = get_column(err, cid, false);
    if(col != nullptr) {
      col->remove_all(err);
      {
        std::lock_guard<std::mutex> lock(m_mutex);
        auto it = m_columns->find(cid);
        if (it != m_columns->end()) 
          m_columns->erase(it);
      }
    }
    cb(err);
  }
  
  std::string to_string(){
    std::lock_guard<std::mutex> lock(m_mutex);

    std::string s("columns=(");
    for(auto it = m_columns->begin(); it != m_columns->end(); ++it){
      s.append(it->second->to_string());
      s.append(",");
    }
    s.append(")");
    return s;
  }

  private:
  std::mutex                  m_mutex;
  std::shared_ptr<ColumnsMap> m_columns;
  State                       m_state;

};
typedef std::shared_ptr<Columns> ColumnsPtr;

}} // namespace server::RS



namespace Env {
class RsColumns {
  public:

  static void init() {
    m_env = std::make_shared<RsColumns>();
  }

  static server::RS::ColumnsPtr get(){
    HT_ASSERT(m_env != nullptr);
    return m_env->m_columns;
  }

  RsColumns() : m_columns(std::make_shared<server::RS::Columns>()) {}
  virtual ~RsColumns(){}

  private:
  server::RS::ColumnsPtr                   m_columns = nullptr;
  inline static std::shared_ptr<RsColumns> m_env = nullptr;
};
}


}
#endif