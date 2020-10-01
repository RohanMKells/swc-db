
/*
 * SWC-DB© Copyright since 2019 Alex Kashirin <kashirin.alex@gmail.com>
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */

#ifndef swcdb_manager_Protocol_mngr_params_ColumnUpdate_h
#define swcdb_manager_Protocol_mngr_params_ColumnUpdate_h

#include "swcdb/core/comm/Serializable.h"

namespace SWC { namespace Protocol { namespace Mngr { namespace Params {


class ColumnUpdate : public Comm::Serializable {
  public:

  ColumnUpdate() {}

  ColumnUpdate(ColumnMng::Function function, 
               const DB::Schema::Ptr& schema, int err) 
              : function(function), schema(schema), err(err) {
  }

  void print(std::ostream& out) {
    out << "ColumnUpdate(func=" << int(function);
    schema->print(out << ' ');
    Error::print(out << ' ', err);
    out << ')';
  }
  
  ColumnMng::Function   function;
  DB::Schema::Ptr       schema;
  int                   err;

  private:

  size_t internal_encoded_length() const {
    return 1
          + schema->encoded_length() 
          + Serialization::encoded_length_vi32(err);
  }
    
  void internal_encode(uint8_t** bufp) const {
    Serialization::encode_i8(bufp, (uint8_t)function);
    schema->encode(bufp);
    Serialization::encode_vi32(bufp, err);
  }
    
  void internal_decode(const uint8_t** bufp, size_t* remainp) {
    function = (ColumnMng::Function)Serialization::decode_i8(bufp, remainp);
    schema = std::make_shared<DB::Schema>(bufp, remainp);
    err = Serialization::decode_vi32(bufp, remainp);
  }

};
  

}}}}

#endif // swcdb_manager_Protocol_mngr_params_ColumnUpdate_h
