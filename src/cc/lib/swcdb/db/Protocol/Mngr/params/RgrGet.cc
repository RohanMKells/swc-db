/*
 * SWC-DB© Copyright since 2019 Alex Kashirin <kashirin.alex@gmail.com>
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */


#include "swcdb/db/Protocol/Mngr/params/RgrGet.h"
#include "swcdb/core/Serialization.h"



namespace SWC { namespace Comm { namespace Protocol {
namespace Mngr { namespace Params {



void RgrGetReq::print(std::ostream& out) const {
  out << "Ranger(cid=" << cid << " rid=" << rid;
  if(!rid) {
    out << " next_range=" << next_range;
    range_begin.print(out << " RangeBegin");
    range_end.print(out << " RangeEnd");
  }
  out << ')';
}

size_t RgrGetReq::internal_encoded_length() const {
  return  Serialization::encoded_length_vi64(cid)
        + Serialization::encoded_length_vi64(rid)
        + (rid ? 0 :
           (range_begin.encoded_length()
            + range_end.encoded_length()
            + 1)
          );
}

void RgrGetReq::internal_encode(uint8_t** bufp) const {
  Serialization::encode_vi64(bufp, cid);
  Serialization::encode_vi64(bufp, rid);
  if(!rid) {
    range_begin.encode(bufp);
    range_end.encode(bufp);
    Serialization::encode_bool(bufp, next_range);
  }
}

void RgrGetReq::internal_decode(const uint8_t** bufp, size_t* remainp) {
  cid = Serialization::decode_vi64(bufp, remainp);
  rid = Serialization::decode_vi64(bufp, remainp);
  if(!rid) {
    range_begin.decode(bufp, remainp, false);
    range_end.decode(bufp, remainp, false);
    next_range = Serialization::decode_bool(bufp, remainp);
  }
}



void RgrGetRsp::print(std::ostream& out) const {
  out << "Ranger(";
  Error::print(out, err);
  if(!err) {
    out << " cid=" << cid << " rid=" << rid;
    Common::Params::HostEndPoints::print(out << ' ');
    if(cid == 1) {
      range_begin.print(out << " RangeBegin");
      range_end.print(out << " RangeEnd");
    }
  }
  out << ')';
}

size_t RgrGetRsp::internal_encoded_length() const {
  return  Serialization::encoded_length_vi32(err)
  + (err ? 0 :
      (Serialization::encoded_length_vi64(cid)
      + Serialization::encoded_length_vi64(rid)
      + Common::Params::HostEndPoints::internal_encoded_length()
      + (cid == 1
        ? (range_end.encoded_length() + range_begin.encoded_length())
        : 0)
      )
    );
}

void RgrGetRsp::internal_encode(uint8_t** bufp) const {
  Serialization::encode_vi32(bufp, err);
  if(!err) {
    Serialization::encode_vi64(bufp, cid);
    Serialization::encode_vi64(bufp, rid);
    Common::Params::HostEndPoints::internal_encode(bufp);
    if(cid == 1) {
      range_end.encode(bufp);
      range_begin.encode(bufp);
    }
  }
}

void RgrGetRsp::internal_decode(const uint8_t** bufp, size_t* remainp) {
  err = Serialization::decode_vi32(bufp, remainp);
  if(!err) {
    cid = Serialization::decode_vi64(bufp, remainp);
    rid = Serialization::decode_vi64(bufp, remainp);
    Common::Params::HostEndPoints::internal_decode(bufp, remainp);
    if(cid == 1) {
      range_end.decode(bufp, remainp, true);
      range_begin.decode(bufp, remainp, true);
    }
  }
}


}}}}}
