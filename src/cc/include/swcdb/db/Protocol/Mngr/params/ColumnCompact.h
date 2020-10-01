
/*
 * SWC-DB© Copyright since 2019 Alex Kashirin <kashirin.alex@gmail.com>
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */

#ifndef swcdb_db_protocol_mngr_params_ColumnCompact_h
#define swcdb_db_protocol_mngr_params_ColumnCompact_h


#include "swcdb/db/Types/Identifiers.h"
#include "swcdb/core/comm/Serializable.h"


namespace SWC { namespace Protocol { namespace Mngr { namespace Params {


class ColumnCompactReq : public Comm::Serializable {
  public:

  ColumnCompactReq(cid_t cid=0);

  virtual ~ColumnCompactReq();
  
  cid_t cid;
  
  std::string to_string() const;

  private:

  size_t internal_encoded_length() const;

  void internal_encode(uint8_t** bufp) const;

  void internal_decode(const uint8_t** bufp, size_t* remainp);

};



class ColumnCompactRsp : public Comm::Serializable {
  public:

  ColumnCompactRsp(int err = Error::OK);

  virtual ~ColumnCompactRsp();

  int err;        

  std::string to_string() const;

  private:

  size_t internal_encoded_length() const;

  void internal_encode(uint8_t** bufp) const;

  void internal_decode(const uint8_t** bufp, size_t* remainp);

};
  

}}}}



#ifdef SWC_IMPL_SOURCE
#include "swcdb/db/Protocol/Mngr/params/ColumnCompact.cc"
#endif 

#endif // swcdb_db_protocol_mngr_params_ColumnCompact_h
