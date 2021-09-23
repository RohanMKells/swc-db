/*
 * SWC-DB© Copyright since 2019 Alex Kashirin <kashirin.alex@gmail.com>
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */


#ifndef swcdb_db_cells_Cell_h
#define swcdb_db_cells_Cell_h


#include "swcdb/core/Serialization.h"
#include "swcdb/core/Buffer.h"
#include "swcdb/core/Time.h"

#include "swcdb/db/Types/Column.h"
#include "swcdb/db/Types/Encoder.h"
#include "swcdb/db/Cells/CellKey.h"


namespace SWC {



/**
 * \defgroup Database The Database Group
 * @brief A group with all related to SWC-DB Database (libswcdb).
 *
 *
 */



/**
 * @brief The SWC-DB Database C++ namespace 'SWC::DB'
 *
 * \ingroup Database
 */
namespace DB {


enum DisplayFlag : uint8_t {
  TIMESTAMP     = 0x01,
  DATETIME      = 0x04,
  BINARY        = 0x08,
  SPECS         = 0x10,
  STATS         = 0x20,
  COLUMN        = 0x40
};

enum OutputFlag : uint8_t {
  NO_TS     = 0x01,
  NO_VALUE  = 0x04,
  NO_ENCODE = 0x08
};


//! The SWC-DB Cells C++ namespace 'SWC::DB::Cells'
namespace Cells {

enum Flag : uint8_t {
  NONE                      = 0x0, // empty instance
  INSERT                    = 0x1,
  DELETE                    = 0x2,
  DELETE_VERSION            = 0x3
};

const char* SWC_CONST_FUNC to_string(Flag flag) noexcept;

Flag SWC_PURE_FUNC flag_from(const uint8_t* rptr, uint32_t len) noexcept;


constexpr const int64_t TIMESTAMP_MIN  = INT64_MIN;
constexpr const int64_t TIMESTAMP_MAX  = INT64_MAX;
constexpr const int64_t TIMESTAMP_NULL = INT64_MIN + 1;
constexpr const int64_t TIMESTAMP_AUTO = INT64_MIN + 2;
constexpr const int64_t AUTO_ASSIGN    = TIMESTAMP_AUTO;

constexpr const uint8_t HAVE_REVISION      =  0x80;
constexpr const uint8_t HAVE_TIMESTAMP     =  0x40;
constexpr const uint8_t AUTO_TIMESTAMP     =  0x20;
constexpr const uint8_t REV_IS_TS          =  0x10;
constexpr const uint8_t HAVE_ENCODER       =  0x2;
constexpr const uint8_t HAVE_ENCODER_MASK  =  0xff - HAVE_ENCODER;
constexpr const uint8_t TS_DESC            =  0x1;

constexpr const uint8_t OP_EQUAL  = 0x1;



class Cell final {
  public:
  typedef std::shared_ptr<Cell> Ptr;

  SWC_CAN_INLINE
  explicit Cell() noexcept
                : own(false), flag(Flag::NONE), control(0),
                  vlen(0), value(nullptr) {
  }

  explicit Cell(const Cell& other);

  explicit Cell(const Cell& other, bool no_value);

  explicit Cell(const uint8_t** bufp, size_t* remainp, bool own=false);

  constexpr SWC_CAN_INLINE
  Cell(Cell&& other) noexcept
      : key(std::move(other.key)),
        own(other.own),
        flag(other.flag),
        control(other.control),
        vlen(other.vlen),
        timestamp(other.timestamp),
        revision(other.revision),
        value(other.value) {
    other.value = nullptr;
    other.vlen = 0;
  }

  Cell& operator=(const Cell&) = delete;

  SWC_CAN_INLINE
  Cell& operator=(Cell&& other) noexcept {
    move(other);
    return *this;
  }

  void move(Cell& other) noexcept;

  void copy(const Cell& other, bool no_value=false);

  SWC_CAN_INLINE
  ~Cell() noexcept {
    _free();
  }

  SWC_CAN_INLINE
  void _free() noexcept {
    if(own && value)
      delete [] value;
  }

  SWC_CAN_INLINE
  void free() noexcept {
    _free();
    vlen = 0;
    value = nullptr;
  }

  constexpr SWC_CAN_INLINE
  void set_time_order_desc(bool desc) noexcept {
    if(desc)
      control |= TS_DESC;
    else if(control & TS_DESC)
      control -= TS_DESC;
  }

  constexpr SWC_CAN_INLINE
  void set_timestamp(int64_t ts) noexcept {
    timestamp = ts;
    control |= HAVE_TIMESTAMP;
  }

  constexpr SWC_CAN_INLINE
  void set_revision(int64_t ts) noexcept {
    revision = ts;
    control |= HAVE_REVISION;
  }

  SWC_CAN_INLINE
  void set_value(uint8_t* v, uint32_t len, bool owner) {
    _free();
    vlen = len;
    value = (own = owner) ? _value(v) : v;
  }

  SWC_CAN_INLINE
  void set_value(const char* v, uint32_t len, bool owner) {
    set_value(reinterpret_cast<uint8_t*>(const_cast<char*>(v)), len, owner);
  }

  SWC_CAN_INLINE
  void set_value(const char* v, bool owner=true) {
    set_value(v, strlen(v), owner);
  }

  SWC_CAN_INLINE
  void set_value(const std::string& v, bool owner=true) {
    set_value(v.c_str(), v.length(), owner);
  }

  void set_value(Types::Encoder encoder, const uint8_t* v, uint32_t len);

  SWC_CAN_INLINE
  void set_value(Types::Encoder encoder, const std::string& v) {
    set_value(encoder, reinterpret_cast<const uint8_t*>(v.c_str()), v.size());
  }

  void get_value(StaticBuffer& v, bool owner=false) const;

  void get_value(std::string& v) const;

  void set_counter(uint8_t op, int64_t v,
                  Types::Column typ = Types::Column::COUNTER_I64,
                  int64_t rev = TIMESTAMP_NULL);

  uint8_t get_counter_op() const;

  int64_t get_counter() const;

  int64_t get_counter(uint8_t& op, int64_t& rev) const;

  void read(const uint8_t** bufp, size_t* remainp, bool owner=false);

  constexpr
  size_t encoded_length(bool no_value=false) const noexcept;

  void write(DynamicBuffer &dst_buf, bool no_value=false) const;

  bool SWC_PURE_FUNC equal(const Cell& other) const noexcept;

  constexpr SWC_CAN_INLINE
  bool removal() const noexcept {
    return flag != Flag::INSERT;
  }

  constexpr
  bool is_removing(const int64_t& rev) const noexcept;

  constexpr SWC_CAN_INLINE
  int64_t get_timestamp() const noexcept {
    return control & HAVE_TIMESTAMP ? timestamp : AUTO_ASSIGN;
  }

  constexpr SWC_CAN_INLINE
  int64_t get_revision() const noexcept {
    return control & HAVE_REVISION ? revision
          : (control & REV_IS_TS ? timestamp : AUTO_ASSIGN );
  }

  SWC_CAN_INLINE
  bool has_expired(const int64_t ttl) const noexcept {
    return ttl &&
           (control & HAVE_TIMESTAMP) &&
           (Time::now_ns() > timestamp + ttl);
  }

  constexpr SWC_CAN_INLINE
  bool have_encoder() const noexcept {
    return control & HAVE_ENCODER;
  }

  void display(std::ostream& out, Types::Column typ = Types::Column::PLAIN,
               uint8_t flags=0, bool meta=false) const;

  SWC_CAN_INLINE
  std::string to_string(Types::Column typ = Types::Column::PLAIN) const {
    std::string s;
    {
      std::stringstream ss;
      print(ss, typ);
      s = ss.str();
    }
    return s;
  }

  void print(std::ostream& out, Types::Column typ) const;

  DB::Cell::Key   key;
  bool            own;
  uint8_t         flag;
  uint8_t         control;
  uint32_t        vlen;
  int64_t         timestamp;
  int64_t         revision;
  uint8_t*        value;

  private:

  SWC_CAN_INLINE
  uint8_t* _value(const uint8_t* v) {
    return vlen
      ? static_cast<uint8_t*>(memcpy(new uint8_t[vlen], v, vlen))
      : nullptr;
  }

};



SWC_CAN_INLINE
Cell::Cell(const Cell& other)
  : key(other.key), own(other.vlen), flag(other.flag),
    control(other.control),
    vlen(other.vlen),
    timestamp(other.timestamp),
    revision(other.revision),
    value(_value(other.value)) {
}

SWC_CAN_INLINE
Cell::Cell(const Cell& other, bool no_value)
  : key(other.key), own(!no_value && other.vlen), flag(other.flag),
    control(no_value ? other.control & HAVE_ENCODER_MASK : other.control),
    vlen(own ? other.vlen : 0),
    timestamp(other.timestamp),
    revision(other.revision),
    value(_value(other.value)) {
}

SWC_CAN_INLINE
Cell::Cell(const uint8_t** bufp, size_t* remainp, bool a_own)
          : own(a_own),
            flag(Serialization::decode_i8(bufp, remainp)) {
  key.decode(bufp, remainp, own);
  control = Serialization::decode_i8(bufp, remainp);

  if(control & HAVE_TIMESTAMP)
    timestamp = Serialization::decode_i64(bufp, remainp);
  else if(control & AUTO_TIMESTAMP)
    timestamp = AUTO_ASSIGN;

  if(control & HAVE_REVISION)
    revision = Serialization::decode_i64(bufp, remainp);
  else if(control & REV_IS_TS)
    revision = timestamp;

  if((vlen = Serialization::decode_vi32(bufp, remainp))) {
    if(*remainp < vlen)
      SWC_THROWF(Error::SERIALIZATION_INPUT_OVERRUN,
        "Read Cell(key=%s) value", key.to_string().c_str());
    value = own ? _value(*bufp) : const_cast<uint8_t*>(*bufp);
    *bufp += vlen;
    *remainp -= vlen;
  } else {
    value = nullptr;
  }
}

SWC_CAN_INLINE
void Cell::move(Cell& other) noexcept {
  _free();
  own       = other.own;
  key.move(other.key);
  flag      = other.flag;
  control   = other.control;
  timestamp = other.timestamp;
  revision  = other.revision;
  value     = other.value;
  vlen      = other.vlen;
  other.value = nullptr;
  other.vlen = 0;
}

SWC_CAN_INLINE
void Cell::copy(const Cell& other, bool no_value) {
  key.copy(other.key);
  flag      = other.flag;
  control   = other.control;
  timestamp = other.timestamp;
  revision  = other.revision;

  if(no_value) {
    control &= HAVE_ENCODER_MASK;
    free();
  } else {
    set_value(other.value, other.vlen, true);
  }
}

SWC_CAN_INLINE
void Cell::get_value(std::string& v) const {
  v.clear();
  if(vlen) {
    StaticBuffer _v;
    get_value(_v);
    v.append(reinterpret_cast<const char*>(_v.base), _v.size);
  }
}

SWC_CAN_INLINE
void Cell::set_counter(uint8_t op, int64_t v, Types::Column typ, int64_t rev) {
  _free();
  own = true;

  switch(typ) {
    case Types::Column::COUNTER_I8:
      v = int8_t(v);
      break;
    case Types::Column::COUNTER_I16:
      v = int16_t(v);
      break;
    case Types::Column::COUNTER_I32:
      v = int32_t(v);
      break;
    default:
      break;
  }

  vlen = 1 + Serialization::encoded_length_vi64(v);
  bool has_rev = op & OP_EQUAL && rev != TIMESTAMP_NULL;
  if(has_rev) {
    op |= HAVE_REVISION;
    vlen += Serialization::encoded_length_vi64(rev);
  }

  uint8_t* ptr = (value = new uint8_t[vlen]);
  Serialization::encode_vi64(&ptr, v);
  *ptr++ = op;
  if(has_rev)
    Serialization::encode_vi64(&ptr, rev);
  // +? i64's storing epochs
}

SWC_CAN_INLINE
uint8_t Cell::get_counter_op() const {
  const uint8_t* ptr = value;
  Serialization::decode_vi64(&ptr);
  return *ptr;
}

SWC_CAN_INLINE
int64_t Cell::get_counter() const {
  const uint8_t *ptr = value;
  return Serialization::decode_vi64(&ptr);
}

SWC_CAN_INLINE
int64_t Cell::get_counter(uint8_t& op, int64_t& rev) const {
  const uint8_t *ptr = value;
  int64_t v = Serialization::decode_vi64(&ptr);
  rev = ((op = *ptr) & HAVE_REVISION)
        ? Serialization::decode_vi64(&++ptr)
        : TIMESTAMP_NULL;
  return v;
}

constexpr SWC_CAN_INLINE
size_t Cell::encoded_length(bool no_value) const noexcept {
  size_t len = key.encoded_length();
  len += 2;
  if(control & HAVE_TIMESTAMP)
    len += 8;
  if(control & HAVE_REVISION)
    len += 8;
  if(no_value)
    return ++len;
  len += Serialization::encoded_length_vi32(vlen);
  return len += vlen;
}

SWC_CAN_INLINE
void Cell::read(const uint8_t** bufp, size_t* remainp, bool owner) {

  flag = Serialization::decode_i8(bufp, remainp);
  key.decode(bufp, remainp, owner);
  control = Serialization::decode_i8(bufp, remainp);

  if(control & HAVE_TIMESTAMP)
    timestamp = Serialization::decode_i64(bufp, remainp);
  else if(control & AUTO_TIMESTAMP)
    timestamp = AUTO_ASSIGN;

  if(control & HAVE_REVISION)
    revision = Serialization::decode_i64(bufp, remainp);
  else if(control & REV_IS_TS)
    revision = timestamp;

  _free();
  own = owner;
  if((vlen = Serialization::decode_vi32(bufp, remainp))) {
    if(*remainp < vlen)
      SWC_THROWF(Error::SERIALIZATION_INPUT_OVERRUN,
        "Read Cell(key=%s) value", key.to_string().c_str());
    value = own ? _value(*bufp) : const_cast<uint8_t*>(*bufp);
    *bufp += vlen;
    *remainp -= vlen;
  } else {
    value = nullptr;
  }
}

SWC_CAN_INLINE
void Cell::write(DynamicBuffer &dst_buf, bool no_value) const {
  dst_buf.ensure(encoded_length( no_value || (no_value = !vlen) ));

  Serialization::encode_i8(&dst_buf.ptr, flag);
  key.encode(&dst_buf.ptr);

  uint8_t ctrl = control;
  if(no_value)
    ctrl &= HAVE_ENCODER_MASK;

  Serialization::encode_i8(&dst_buf.ptr, ctrl);
  if(ctrl & HAVE_TIMESTAMP)
    Serialization::encode_i64(&dst_buf.ptr, timestamp);
  if(ctrl & HAVE_REVISION)
    Serialization::encode_i64(&dst_buf.ptr, revision);

  if(no_value) {
    Serialization::encode_i8(&dst_buf.ptr, 0);
  } else {
    Serialization::encode_vi32(&dst_buf.ptr, vlen);
    dst_buf.add_unchecked(value, vlen);
  }
}

constexpr SWC_CAN_INLINE
bool Cell::is_removing(const int64_t& rev) const noexcept {
  return rev != AUTO_ASSIGN && removal() && (
    (flag == DELETE  && get_timestamp() >= rev )
    ||
    (flag == DELETE_VERSION && get_timestamp() == rev )
    );
}



}}}

#ifdef SWC_IMPL_SOURCE
#include "swcdb/db/Cells/Cell.cc"
#endif

#endif // swcdb_db_Cells_Cell_h
