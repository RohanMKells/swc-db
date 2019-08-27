
/*
 * Copyright (C) 2019 SWC-DB (author: Kashirin Alex (kashirin.alex@gmail.com))
 */

#ifndef swc_db_protocol_params_MngRsId_h
#define swc_db_protocol_params_MngRsId_h

#include "swcdb/lib/core/Serializable.h"
#include "HostEndPoints.h"

namespace SWC {
namespace Protocol {
namespace Params {


  class MngRsId  : public HostEndPoints {
  public:

    enum Flag {
      MNGR_ASSIGNED = 1,
      MNGR_NOT_ACTIVE = 2,
      MNGR_REASSIGN = 3,
      MNGR_REREQ = 4,
      RS_REQ = 5, // >= params with host endpoints
      RS_ACK = 6,
      RS_DISAGREE = 7,
      RS_SHUTTINGDOWN = 8
    };

    MngRsId() {}

    MngRsId(uint64_t rs_id, Flag flag) 
            : rs_id(rs_id), flag(flag){
    }
    MngRsId(uint64_t rs_id, Flag flag, const EndPoints& endpoints) 
              : rs_id(rs_id), flag(flag), HostEndPoints(endpoints){     
    }

    uint64_t        rs_id; 
    Flag            flag;
    Types::Fs       fs;

  private:

    uint8_t encoding_version() const {
      return 1;
    }
    
    size_t encoded_length_internal() const {
      size_t len = 1;
      if(flag != Flag::MNGR_NOT_ACTIVE)
        len += Serialization::encoded_length_vi64(rs_id);

      if(flag >= Flag::RS_REQ) 
        len +=  HostEndPoints::encoded_length_internal();
      
      if(flag == Flag::MNGR_ASSIGNED)
        len++; // fs-type
      return len;
    }
    
    void encode_internal(uint8_t **bufp) const {
      Serialization::encode_i8(bufp, (uint8_t)flag);
      if(flag != Flag::MNGR_NOT_ACTIVE)
        Serialization::encode_vi64(bufp, rs_id);
      
      if(flag >= Flag::RS_REQ)
        HostEndPoints::encode_internal(bufp);

      if(flag == Flag::MNGR_ASSIGNED)
        Serialization::encode_i8(
          bufp, (int8_t)Env::FsInterface::interface()->get_type());
    }
    
    void decode_internal(uint8_t version, const uint8_t **bufp, 
                        size_t *remainp) {
      flag = (Flag)Serialization::decode_i8(bufp, remainp);
      if(flag != Flag::MNGR_NOT_ACTIVE)
        rs_id = Serialization::decode_vi64(bufp, remainp);
      
      if(flag >= Flag::RS_REQ)
        HostEndPoints::decode_internal(version, bufp, remainp);
      
      if(flag == Flag::MNGR_ASSIGNED)
        fs = (Types::Fs)Serialization::decode_i8(bufp, remainp);
    }

  };
  

}}}

#endif // swc_db_protocol_params_MngRsId_h
