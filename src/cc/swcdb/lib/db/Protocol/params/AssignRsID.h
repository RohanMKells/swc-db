
/*
 * Copyright (C) 2019 SWC-DB (author: Kashirin Alex (kashirin.alex@gmail.com))
 */

#ifndef swc_db_protocol_params_AssignRsID_h
#define swc_db_protocol_params_AssignRsID_h

#include "swcdb/lib/core/Serializable.h"
#include "HostEndPoints.h"

namespace SWC {
namespace Protocol {
namespace Params {


  class AssignRsID : public Serializable {
  public:

    enum Flag {
      MNGR_ASSIGNED = 1,
      MNGR_NOT_ACTIVE = 2,
      RS_REQ = 3,
      RS_ACK = 4,
      RS_DISAGREE = 5,
      MNGR_REASSIGN = 6,
    };

    AssignRsID() {}

    AssignRsID(uint64_t rs_id, Flag flag, 
                  EndPoints endpoints) 
                : rs_id(rs_id), flag(flag),
                  host(endpoints.size()==0?nullptr:new HostEndPoints(endpoints)){}

    HostEndPoints* host; 
    uint64_t rs_id; 
    Flag flag;

  private:

    uint8_t encoding_version() const {
      return 1;
    }
    
    size_t encoded_length_internal() const {
      return 1
        +(flag != Flag::MNGR_NOT_ACTIVE 
          ? Serialization::encoded_length_vi64(rs_id) : 0)
        +(flag >= Flag::RS_REQ 
          ? host->encoded_length() : 0);
    }
    
    void encode_internal(uint8_t **bufp) const {
      Serialization::encode_i8(bufp, (uint8_t)flag);
      if(flag != Flag::MNGR_NOT_ACTIVE)
        Serialization::encode_vi64(bufp, rs_id);
      
      if(flag >= Flag::RS_REQ)
        host->encode(bufp);
    }
    
    void decode_internal(uint8_t version, const uint8_t **bufp, 
                        size_t *remainp) {
      flag = (Flag)Serialization::decode_i8(bufp, remainp);
      if(flag != Flag::MNGR_NOT_ACTIVE)
        rs_id = Serialization::decode_vi64(bufp, remainp);
      
      if(flag >= Flag::RS_REQ){
        host = new HostEndPoints();
        host->decode(bufp, remainp);
      }
    }

  };
  

}}}

#endif // swc_db_protocol_params_AssignRsID_h
