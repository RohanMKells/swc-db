/*
 * Copyright (C) 2019 SWC-DB (author: Kashirin Alex (kashirin.alex@gmail.com))
 */


#ifndef swcdb_lib_db_Columns_Column_h
#define swcdb_lib_db_Columns_Column_h

#include "Schema.h"
#include "Range.h"

#include <mutex>
#include <memory>
#include <unordered_map>


namespace SWC {

typedef std::unordered_map<int64_t, RangePtr> RangesMap;
typedef std::pair<int64_t, RangePtr> RangesMapPair;


class Column : public std::enable_shared_from_this<Column> {
  
  public:

  Column(FS::InterfacePtr fs, int64_t id)
        : m_fs(fs), cid(id),
          ranges(std::make_shared<RangesMap>()) {
    
    std::string col_range_path(Range::get_path(cid));
    m_err = 0;
    if(!m_fs->get_fs()->exists(m_err, col_range_path))
      m_fs->get_fs()->mkdirs(m_err, col_range_path);
      if(m_err == 17)
        m_err = 0;
  }

  virtual ~Column(){}

  int has_err(){
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_err;
  }

  void ranges_by_fs(int &err, FS::IdEntries_t &entries){
    m_fs->get_structured_ids(err, Range::get_path(cid), entries);
  }

  RangePtr get_range(int64_t rid, bool initialize=false, 
                     Files::RsDataPtr rs_data=nullptr){
    std::lock_guard<std::mutex> lock(m_mutex);

    auto it = ranges->find(rid);
    if (it != ranges->end())
      return it->second;

    if(initialize) {
      RangePtr range = std::make_shared<Range>(m_fs, cid, rid, schema);
      if(rs_data == nullptr || range->load(rs_data)){
        ranges->insert(RangesMapPair(rid, range));
      }
      return range;
    }
    return nullptr;
  }

  private:

  std::mutex        m_mutex;
  int               m_err;
  FS::InterfacePtr  m_fs;
  int64_t           cid;
  SchemaPtr         schema;
  std::shared_ptr<RangesMap> ranges;

};
typedef std::shared_ptr<Column> ColumnPtr;

}

#endif