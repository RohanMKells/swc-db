/*
 * SWC-DB© Copyright since 2019 Alex Kashirin <kashirin.alex@gmail.com>
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */


#ifndef swc_manager_db_Columns_h
#define swc_manager_db_Columns_h

#include "swcdb/db/Types/MetaColumn.h"
#include "swcdb/fs/Interface.h"

#include "swcdb/manager/db/ColumnCfg.h"
#include "swcdb/manager/db/Column.h"
#include "swcdb/manager/db/Schema.h"

#include <memory>
#include <unordered_map>
#include <iostream>

namespace SWC { namespace Manager {



class Columns final : private std::unordered_map<cid_t, Column::Ptr> {

  public:

  static void columns_by_fs(int &err, FS::IdEntries_t &entries) {
    Env::FsInterface::interface()->get_structured_ids(
      err, DB::RangeBase::get_column_path(), entries);
  }

  typedef Columns* Ptr;

  Columns()  {}

  ~Columns() { }

  void reset() {
    Mutex::scope lock(m_mutex);
    clear();
  }

  void state(int& err) {
    Mutex::scope lock(m_mutex);
    for(auto it = begin(); !err && it != end(); ++it)
      it->second->state(err);
  }

  bool is_an_initialization(int &err, const DB::Schema::Ptr& schema) {
    Column::Ptr col = nullptr;
    {
      Mutex::scope lock(m_mutex);
      auto it = find(schema->cid);
      if (it != end())
        return false;

      emplace(schema->cid, col = std::make_shared<Column>(schema));
    }
    col->init(err);
    return true;
  }

  Column::Ptr get_column(int &err, const cid_t cid) {
    Mutex::scope lock(m_mutex);
    auto it = find(cid);
    if(it != end())
      return it->second;
    err = Error::COLUMN_NOT_EXISTS;
    return nullptr;
  }

  Range::Ptr get_next_unassigned() {
    Range::Ptr range = nullptr;
    iterator it;
    Mutex::scope lock(m_mutex);
    for(cid_t cid = 1; cid <= Files::Schema::SYS_CID_END; ++cid) {
      if((it = find(cid)) != end() && 
         (range = it->second->get_next_unassigned()))
        return range;
    }
    for(it = begin(); it != end(); ++it) {
      if((range = it->second->get_next_unassigned()))
        return range;
    }
    return range;
  }

  void set_rgr_unassigned(rgrid_t rgrid) {
    Mutex::scope lock(m_mutex);
    for(auto it = begin(); it != end(); ++it)
      it->second->set_rgr_unassigned(rgrid);
  }

  void change_rgr(rgrid_t rgrid_old, rgrid_t rgrid) {
    Mutex::scope lock(m_mutex);
    for(auto it = begin(); it != end(); ++it)
      it->second->change_rgr(rgrid_old, rgrid);
  }

  Column::Ptr get_need_health_check(int64_t ts, uint32_t ms) {
    Mutex::scope lock(m_mutex);
    for(auto it = begin(); it != end(); ++it) {
      if(it->second->need_health_check(ts, ms))
        return it->second;
    }
    return nullptr;
  }

  void remove(int&, const cid_t cid) {
    Mutex::scope lock(m_mutex);
    auto it = find(cid);
    if (it != end())
      erase(it);
  }

  void print(std::ostream& out) {
    out << "ColumnsAssignment:";
    Mutex::scope lock(m_mutex);
    for(auto it = begin(); it != end(); ++it)
      it->second->print(out << "\n ");
  }

  private:
  Mutex   m_mutex;

};

}} // namespace SWC::Manager

#endif // swc_manager_db_Columns_h