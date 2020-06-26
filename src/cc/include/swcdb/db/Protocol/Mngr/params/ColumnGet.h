
/*
 * Copyright Since 2019 SWC-DB© [author: Kashirin Alex kashirin.alex@gmail.com]
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */

#ifndef swc_db_protocol_mngr_params_ColumnGet_h
#define swc_db_protocol_mngr_params_ColumnGet_h


#include "swcdb/core/Serializable.h"
#include "swcdb/db/Columns/Schema.h"


namespace SWC { namespace Protocol { namespace Mngr { namespace Params {


class ColumnGetReq  : public Serializable {
  public:

  enum Flag {
    SCHEMA_BY_ID    = 0x0,
    SCHEMA_BY_NAME  = 0x1,
    ID_BY_NAME      = 0x2
  };

  ColumnGetReq();

  ColumnGetReq(Flag flag, const std::string& name);

  ColumnGetReq(Flag flag, cid_t cid);

  virtual ~ColumnGetReq();

  Flag        flag;
  std::string name;
  cid_t       cid {};

  private:

  size_t internal_encoded_length() const;

  void internal_encode(uint8_t** bufp) const;

  void internal_decode(const uint8_t** bufp, size_t* remainp);

};



class ColumnGetRsp  : public Serializable {
  public:

  ColumnGetRsp();

  ColumnGetRsp(ColumnGetReq::Flag flag, const DB::Schema::Ptr& schema);

  virtual ~ColumnGetRsp();

  ColumnGetReq::Flag  flag;
  DB::Schema::Ptr     schema = nullptr;
  cid_t               cid {};

  private:

  size_t internal_encoded_length() const;

  void internal_encode(uint8_t** bufp) const;

  void internal_decode(const uint8_t** bufp, size_t* remainp);

};

}}}}



#ifdef SWC_IMPL_SOURCE
#include "swcdb/db/Protocol/Mngr/params/ColumnGet.cc"
#endif 

#endif // swc_db_protocol_params_ColumnGetRsp_h
