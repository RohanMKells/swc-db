
/*
 * SWC-DB© Copyright since 2019 Alex Kashirin <kashirin.alex@gmail.com>
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */

#ifndef swcdb_manager_Protocol_mngr_params_ColumnUpdate_h
#define swcdb_manager_Protocol_mngr_params_ColumnUpdate_h

#include "swcdb/core/comm/Serializable.h"

namespace SWC { namespace Comm { namespace Protocol {
namespace Mngr { namespace Params {


class ColumnUpdate : public Serializable {
  public:

  ColumnUpdate() {}

  ColumnUpdate(ColumnMng::Function function,
               const DB::Schema::Ptr& schema, int err, uint64_t id)
              : function(function), id(id), schema(schema), err(err) {
  }

  ColumnUpdate(ColumnMng::Function function,
               cid_t cid_begin, cid_t cid_end,
               const std::vector<cid_t>& columns)
              : function(function), id(0),
                columns(columns), cid_begin(cid_begin), cid_end(cid_end),
                err(Error::OK) {
  }

  void print(std::ostream& out) {
    out << "ColumnUpdate(func=" << int(function)
        << " id=" << id;
    if(function == ColumnMng::Function::INTERNAL_EXPECT) {
      out << " cid-begin=" << cid_begin
          << " cid-end=" << cid_end
          << " columns=[";
      for(cid_t cid : columns)
        out << cid << ',';
      out << ']';

    } else {
      schema->print(out << ' ');
      Error::print(out << ' ', err);
    }
    out << ')';
  }

  ColumnMng::Function function;
  uint64_t            id;
  std::vector<cid_t>  columns;
  cid_t               cid_begin;
  cid_t               cid_end;
  DB::Schema::Ptr     schema;
  int                 err;

  private:

  size_t internal_encoded_length() const override {
    size_t sz = 1 + Serialization::encoded_length_vi64(id);
    switch(function) {
      case ColumnMng::Function::INTERNAL_EXPECT: {
        sz += Serialization::encoded_length_vi64(cid_begin);
        sz += Serialization::encoded_length_vi64(cid_end);
        sz += Serialization::encoded_length_vi64(columns.size());
        for(const cid_t cid : columns)
          sz += Serialization::encoded_length_vi64(cid);
        break;
      }
      default: {
        sz += schema->encoded_length()
            + Serialization::encoded_length_vi32(err);
        break;
      }
    }
    return sz;
  }

  void internal_encode(uint8_t** bufp) const override {
    Serialization::encode_i8(bufp, function);
    Serialization::encode_vi64(bufp, id);
    switch(function) {
      case ColumnMng::Function::INTERNAL_EXPECT: {
        Serialization::encode_vi64(bufp, cid_begin);
        Serialization::encode_vi64(bufp, cid_end);
        Serialization::encode_vi64(bufp, columns.size());
        for(const cid_t cid : columns)
          Serialization::encode_vi64(bufp, cid);
        break;
      }
      default: {
        schema->encode(bufp);
        Serialization::encode_vi32(bufp, err);
        break;
      }
    }
  }

  void internal_decode(const uint8_t** bufp, size_t* remainp) override {
    function = ColumnMng::Function(Serialization::decode_i8(bufp, remainp));
    id = Serialization::decode_vi64(bufp, remainp);
    switch(function) {
      case ColumnMng::Function::INTERNAL_EXPECT: {
        cid_begin = Serialization::decode_vi64(bufp, remainp);
        cid_end = Serialization::decode_vi64(bufp, remainp);
        columns.clear();
        columns.resize(Serialization::decode_vi64(bufp, remainp));
        for(auto it = columns.begin(); it < columns.end(); ++it)
          *it = Serialization::decode_vi64(bufp, remainp);
        break;
      }
      default : {
        schema = std::make_shared<DB::Schema>(bufp, remainp);
        err = Serialization::decode_vi32(bufp, remainp);
        break;
      }
    }
  }

};


}}}}}

#endif // swcdb_manager_Protocol_mngr_params_ColumnUpdate_h
