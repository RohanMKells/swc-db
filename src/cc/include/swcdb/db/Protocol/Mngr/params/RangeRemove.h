/*
 * SWC-DB© Copyright since 2019 Alex Kashirin <kashirin.alex@gmail.com>
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */

#ifndef swcdb_db_protocol_mngr_params_RangeRemove_h
#define swcdb_db_protocol_mngr_params_RangeRemove_h

#include "swcdb/core/comm/Serializable.h"


namespace SWC { namespace Comm { namespace Protocol {
namespace Mngr { namespace Params {


class RangeRemoveReq final : public Serializable {
  public:

  SWC_CAN_INLINE
  RangeRemoveReq(cid_t cid=0, rid_t rid=0) noexcept
                : cid(cid), rid(rid) {
  }

  //~RangeRemoveReq() { }

  cid_t        cid;
  rid_t        rid;

  std::string to_string() const {
    std::string s("RangeRemoveReq(");
    s.append("cid=");
    s.append(std::to_string(cid));
    s.append(" rid=");
    s.append(std::to_string(rid));
    return s;
  }

  private:

  size_t internal_encoded_length() const override {
    return Serialization::encoded_length_vi64(cid)
         + Serialization::encoded_length_vi64(rid);
  }

  void internal_encode(uint8_t** bufp) const override {
    Serialization::encode_vi64(bufp, cid);
    Serialization::encode_vi64(bufp, rid);
  }

  void internal_decode(const uint8_t** bufp, size_t* remainp) override {
    cid = Serialization::decode_vi64(bufp, remainp);
    rid = Serialization::decode_vi64(bufp, remainp);
  }

};



class RangeRemoveRsp final : public Serializable {
  public:

  SWC_CAN_INLINE
  RangeRemoveRsp(int err = Error::OK) noexcept : err(err) { }

  //~RangeRemoveRsp() { }

  int             err;

  std::string to_string() const {
    std::string s("RangeRemoveRsp(");
    s.append("err=");
    s.append(std::to_string(err));
    s.append("(");
    s.append(Error::get_text(err));
    s.append(")");
    s.append(")");
    return s;
  }

  private:

  size_t internal_encoded_length() const override {
    return Serialization::encoded_length_vi32(err);
  }

  void internal_encode(uint8_t** bufp) const override {
    Serialization::encode_vi32(bufp, err);
  }

  void internal_decode(const uint8_t** bufp, size_t* remainp) override {
    err = Serialization::decode_vi32(bufp, remainp);
  }

};


}}}}}

#endif // swcdb_db_protocol_mngr_params_RangeRemove_h
