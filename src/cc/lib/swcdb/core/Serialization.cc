/*
 * Copyright Since 2019 SWC-DB© [author: Kashirin Alex kashirin.alex@gmail.com]
 */


#include "swcdb/core/Serialization.h"


//#ifdef SWC_IMPL_SOURCE
# define SWC_CAN_INLINE  \
  __attribute__((__always_inline__, __artificial__)) \
  extern inline
//#else 
//# define SWC_CAN_INLINE 
//#endif

#define SWC_THROW_OVERRUN(_s_) \
  SWC_THROWF(Error::SERIALIZATION_INPUT_OVERRUN, "Error decoding %s", _s_)
#define SWC_THROW_UNPOSSIBLE(_s_) \
  SWC_THROWF(Error::UNPOSSIBLE, "%s", _s_)

extern "C" { }

namespace SWC { namespace Serialization {

const uint64_t MAX_V1B = 0x7f;
const uint64_t MAX_V2B = 0x3fff;
const uint64_t MAX_V3B = 0x1fffff;
const uint64_t MAX_V4B = 0x0fffffff;
const uint64_t MAX_V5B = 0x07ffffffff;
const uint64_t MAX_V6B = 0x03ffffffffff;
const uint64_t MAX_V7B = 0x01ffffffffffff;
const uint64_t MAX_V8B = 0x00ffffffffffffff;
const uint64_t MAX_V9B = 0x7fffffffffffffff;

const uint8_t MAX_LEN_VINT24 = 4;
const uint8_t MAX_LEN_VINT32 = 5;
const uint8_t MAX_LEN_VINT64 = 10;


SWC_CAN_INLINE 
void memcopy(uint8_t* dest, const uint8_t** bufp, size_t len) {
  memcpy(dest, *bufp, len);
  *bufp += len;

  //for(; len; --len, ++dest, ++*bufp) *dest = **bufp;
}

SWC_CAN_INLINE 
void memcopy(uint8_t** bufp, const uint8_t* src, size_t len) {  
  memcpy(*bufp, src, len);
  *bufp += len;

  //for(; len; --len, ++*bufp, ++src) **bufp = *src;
}

SWC_CAN_INLINE 
void decode_needed_one(size_t* remainp) {
  if(!*remainp)
    SWC_THROW(Error::SERIALIZATION_INPUT_OVERRUN, 
              "Zero byte remain need 1 byte");
  --*remainp;
}

SWC_CAN_INLINE 
void decode_needed(size_t* remainp, size_t len) {
  if(*remainp < len)
      SWC_THROWF(Error::SERIALIZATION_INPUT_OVERRUN, 
                "Need %llu bytes but only %llu remain", len, *remainp);
  *remainp -= len;          
}

SWC_CAN_INLINE 
void encode_i8(uint8_t** bufp, uint8_t val) {
  **bufp = val;
  ++*bufp;
}

SWC_CAN_INLINE 
uint8_t decode_i8(const uint8_t** bufp, size_t* remainp) {
  decode_needed_one(remainp);
  return *(*bufp)++;
}

SWC_CAN_INLINE 
uint8_t decode_byte(const uint8_t** bufp, size_t* remainp) {
  return decode_i8(bufp, remainp);
}

SWC_CAN_INLINE 
void encode_bool(uint8_t** bufp, bool bval) {
  encode_i8(bufp, bval);
}

SWC_CAN_INLINE 
bool decode_bool(const uint8_t** bufp, size_t* remainp) {
  return decode_i8(bufp, remainp);
}

SWC_CAN_INLINE 
void encode_i16(uint8_t** bufp , uint16_t val) {
  memcopy(bufp, (const uint8_t*)&val, 2);
}

SWC_CAN_INLINE 
uint16_t decode_i16(const uint8_t** bufp, size_t* remainp) {
  decode_needed(remainp, 2);
  uint16_t val;
  memcopy((uint8_t*)&val, bufp, 2);
  return val;
}

SWC_CAN_INLINE 
void encode_i24(uint8_t** bufp , uint24_t val) {
  memcopy(bufp, (const uint8_t*)&val, 3);
}

SWC_CAN_INLINE 
uint24_t decode_i24(const uint8_t** bufp, size_t* remainp) {
  decode_needed(remainp, 3);
  uint24_t val;
  memcopy((uint8_t*)&val, bufp, 3);
  return val;
}

SWC_CAN_INLINE 
void encode_i32(uint8_t** bufp, uint32_t val) {
  memcopy(bufp, (const uint8_t*)&val, 4);
}

SWC_CAN_INLINE 
uint32_t decode_i32(const uint8_t** bufp, size_t* remainp) {
  decode_needed(remainp, 4);
  uint32_t val;
  memcopy((uint8_t*)&val, bufp, 4);
  return val;
}

SWC_CAN_INLINE 
void encode_i64(uint8_t** bufp, uint64_t val) {
  memcopy(bufp, (const uint8_t*)&val, 8);
}

SWC_CAN_INLINE 
uint64_t decode_i64(const uint8_t** bufp, size_t* remainp) {
  decode_needed(remainp, 8);
  uint64_t val;
  memcopy((uint8_t*)&val, bufp, 8);
  return val;
}

#define SWC_ENCODE_VI_0(_p_, _v_) \
  if(_v_ <= MAX_V1B) { **_p_ = _v_; ++*_p_; return; } 

#define SWC_ENCODE_VI_1(_p_, _v_) \
  **_p_ = _v_ | 0x80; ++*_p_; _v_ >>= 7; \
  SWC_ENCODE_VI_0(_p_, _v_);

#define SWC_ENCODE_VI(_p_, _v_, _shifts_) \
  SWC_ENCODE_VI_0(_p_, _v_); \
  for(uint8_t n=0; n < _shifts_; ++n) { SWC_ENCODE_VI_1(_p_, _v_); } \
  SWC_THROW_UNPOSSIBLE("breached encoding length");


#define SWC_DECODE_NEED_BYTE(_r_) \
  if(!*_r_) SWC_THROW(Error::SERIALIZATION_INPUT_OVERRUN, \
                      "Zero byte remain need 1 byte"); \
  --*_r_;

#define SWC_DECODE_VI_(_v_, _tmp_, _p_, _shift_) \
  _v_ |= (_tmp_ = **_p_ & 0x7f) <<= _shift_; \
  if(!(*(*_p_)++ & 0x80)) return _v_;

#define SWC_DECODE_VI_1(_v_, _tmp_, _p_, _r_, _shift_) \
  SWC_DECODE_NEED_BYTE(_r_);  \
  SWC_DECODE_VI_(_v_, _tmp_, _p_, _shift_);

#define SWC_DECODE_VI(_t_, _p_, _r_, _bits_, _name_) \
  _t_ n = 0; _t_ tmp; for(uint8_t shift=0; *_r_ ; shift+=7) { \
    --*_r_; SWC_DECODE_VI_(n, tmp, _p_, shift); \
    if(shift == _bits_) SWC_THROW_OVERRUN(_name_); \
  } \
  SWC_THROW(Error::SERIALIZATION_INPUT_OVERRUN, \
            "Zero byte remain need 1 byte");


SWC_CAN_INLINE 
int encoded_length_vi24(uint24_t val) {
  return 
  (val <= MAX_V1B ? 1 : 
   (val <= MAX_V2B ? 2 : 
    (val <= MAX_V3B ? 3 : 4)));
}

SWC_CAN_INLINE 
void encode_vi24(uint8_t** bufp, uint24_t val) {
  //SWC_ENCODE_VI(bufp, val, 3);
  SWC_ENCODE_VI_0(bufp, val);
  SWC_ENCODE_VI_1(bufp, val);
  SWC_ENCODE_VI_1(bufp, val);
  SWC_ENCODE_VI_1(bufp, val);
  SWC_THROW_UNPOSSIBLE("breached encoding length");
} 

SWC_CAN_INLINE 
uint24_t decode_vi24(const uint8_t** bufp, size_t* remainp) {
  //SWC_DECODE_VI(uint24_t, bufp, remainp, 21, "vint24");
  uint24_t n = 0; uint24_t tmp;
  SWC_DECODE_VI_1(n, tmp, bufp, remainp, 0);
  SWC_DECODE_VI_1(n, tmp, bufp, remainp, 7);
  SWC_DECODE_VI_1(n, tmp, bufp, remainp, 14);
  SWC_DECODE_VI_1(n, tmp, bufp, remainp, 21);
  SWC_THROW_OVERRUN("vint24");
}
SWC_CAN_INLINE 
uint24_t decode_vi24(const uint8_t** bufp) {
  size_t remain = 4;
  return decode_vi24(bufp, &remain);
}


SWC_CAN_INLINE 
int encoded_length_vi32(uint32_t val) {
  return 
  (val <= MAX_V1B ? 1 : 
   (val <= MAX_V2B ? 2 : 
    (val <= MAX_V3B ? 3 : 
     (val <= MAX_V4B ? 4 : 5))));
}

SWC_CAN_INLINE 
void encode_vi32(uint8_t** bufp, uint32_t val) {
  //SWC_ENCODE_VI(bufp, val, 4);
  SWC_ENCODE_VI_0(bufp, val);
  SWC_ENCODE_VI_1(bufp, val);
  SWC_ENCODE_VI_1(bufp, val);
  SWC_ENCODE_VI_1(bufp, val);
  SWC_ENCODE_VI_1(bufp, val);
  SWC_THROW_UNPOSSIBLE("breached encoding length");
} 

SWC_CAN_INLINE 
uint32_t decode_vi32(const uint8_t** bufp, size_t* remainp) {
  SWC_DECODE_VI(uint32_t, bufp, remainp, 28, "vint32");
  /*
  uint32_t n = 0; uint32_t tmp;
  SWC_DECODE_VI_1(n, tmp, bufp, remainp, 0);
  SWC_DECODE_VI_1(n, tmp, bufp, remainp, 7);
  SWC_DECODE_VI_1(n, tmp, bufp, remainp, 14);
  SWC_DECODE_VI_1(n, tmp, bufp, remainp, 21);
  SWC_DECODE_VI_1(n, tmp, bufp, remainp, 28);
  SWC_THROW_OVERRUN("vint32");
  */
}

SWC_CAN_INLINE 
uint32_t decode_vi32(const uint8_t** bufp) {
  size_t remain = 5;
  return decode_vi32(bufp, &remain);
}

SWC_CAN_INLINE 
int encoded_length_vi64(uint64_t val) {
  return 
  (val <= MAX_V1B ? 1 : 
   (val <= MAX_V2B ? 2 : 
    (val <= MAX_V3B ? 3 : 
     (val <= MAX_V4B ? 4 : 
      (val <= MAX_V5B ? 5 : 
       (val <= MAX_V6B ? 6 : 
        (val <= MAX_V7B ? 7 : 
         (val <= MAX_V8B ? 8 : 
          (val <= MAX_V9B ? 9 : 10)))))))));
}

SWC_CAN_INLINE 
void encode_vi64(uint8_t** bufp, uint64_t val) {
  SWC_ENCODE_VI(bufp, val, 9);
  /*
  SWC_ENCODE_VI_0(bufp, val);
  SWC_ENCODE_VI_1(bufp, val);
  SWC_ENCODE_VI_1(bufp, val);
  SWC_ENCODE_VI_1(bufp, val);
  SWC_ENCODE_VI_1(bufp, val);
  SWC_ENCODE_VI_1(bufp, val);
  SWC_ENCODE_VI_1(bufp, val);
  SWC_ENCODE_VI_1(bufp, val);
  SWC_ENCODE_VI_1(bufp, val);
  SWC_ENCODE_VI_1(bufp, val);
  SWC_THROW_UNPOSSIBLE("breached encoding length");
  */
} 

SWC_CAN_INLINE 
uint64_t decode_vi64(const uint8_t** bufp, size_t* remainp) {
  SWC_DECODE_VI(uint64_t, bufp, remainp, 63, "vint64");
  /*
  uint64_t n = 0; uint64_t tmp;
  SWC_DECODE_VI_1(n, tmp, bufp, remainp, 0);
  SWC_DECODE_VI_1(n, tmp, bufp, remainp, 7);
  SWC_DECODE_VI_1(n, tmp, bufp, remainp, 14);
  SWC_DECODE_VI_1(n, tmp, bufp, remainp, 21);
  SWC_DECODE_VI_1(n, tmp, bufp, remainp, 28);
  SWC_DECODE_VI_1(n, tmp, bufp, remainp, 35);
  SWC_DECODE_VI_1(n, tmp, bufp, remainp, 42);
  SWC_DECODE_VI_1(n, tmp, bufp, remainp, 49);
  SWC_DECODE_VI_1(n, tmp, bufp, remainp, 56);
  SWC_DECODE_VI_1(n, tmp, bufp, remainp, 63);
  SWC_THROW_OVERRUN("vint64");
  */
}

SWC_CAN_INLINE 
uint64_t decode_vi64(const uint8_t** bufp) {
  size_t remain = 10;
  return decode_vi64(bufp, &remain);
}


SWC_CAN_INLINE 
size_t encoded_length_bytes32(int32_t len) {
  return len + 4;
}

SWC_CAN_INLINE 
void encode_bytes32(uint8_t** bufp, const void* data, int32_t len) {
  encode_i32(bufp, len);
  memcopy(bufp, (const uint8_t*)data, len);
}


SWC_CAN_INLINE 
uint8_t* decode_bytes32(const uint8_t** bufp, size_t* remainp, uint32_t* lenp) {
  *lenp = decode_i32(bufp, remainp);
  decode_needed(remainp, *lenp);
  uint8_t* out = (uint8_t *)*bufp;
  *bufp += *lenp;
  return out;
}

SWC_CAN_INLINE 
void encode_bytes(uint8_t** bufp, const void* data, int32_t len) {
  memcopy(bufp, (const uint8_t*)data, len);
}

SWC_CAN_INLINE 
uint8_t* decode_bytes(const uint8_t** bufp, size_t* remainp, uint32_t len) {
  decode_needed(remainp, len);
  uint8_t* out = (uint8_t *)*bufp;
  *bufp += len;
  return out;
}

SWC_CAN_INLINE 
size_t encoded_length_str16(const char* str) {
  return 2 + (!str ? 0 : strlen(str)) + 1;
}

SWC_CAN_INLINE 
size_t encoded_length_str16(const std::string& str) {
  return 2 + str.length() + 1;
}

SWC_CAN_INLINE 
void encode_str16(uint8_t** bufp, const void* str, uint16_t len) {
  encode_i16(bufp, len);
  if(len) 
    memcopy(bufp, (const uint8_t*)str, len);
  **bufp = 0;
  ++*bufp;
}

SWC_CAN_INLINE 
void encode_str16(uint8_t** bufp, const char* str) {
  uint16_t len = !str ? 0 : strlen(str);
  encode_str16(bufp, str, len);
}

SWC_CAN_INLINE 
const char* decode_str16(const uint8_t** bufp, size_t* remainp) {
  uint16_t len;
  return decode_str16(bufp, remainp, &len);
}

SWC_CAN_INLINE 
char* decode_str16(const uint8_t** bufp, size_t* remainp, uint16_t *lenp) {
  *lenp = decode_i16(bufp, remainp);
  decode_needed(remainp, *lenp+1);
  char* str = (char *)*bufp;
  *bufp += *lenp;
  if(**bufp != 0)
    SWC_THROW_OVERRUN("str16");
  ++*bufp;
  return str;
}

SWC_CAN_INLINE 
size_t encoded_length_vstr(size_t len) {
  return encoded_length_vi64(len) + len + 1;
}

SWC_CAN_INLINE 
size_t encoded_length_vstr(const char* s) {
  return encoded_length_vstr(s ? strlen(s) : 0);
}

SWC_CAN_INLINE 
size_t encoded_length_vstr(const std::string& s) {
  return encoded_length_vstr(s.length());
}

SWC_CAN_INLINE 
void encode_vstr(uint8_t** bufp, const void* buf, size_t len) {
  encode_vi64(bufp, len);
  if(len) 
    memcopy(bufp, (const uint8_t*)buf, len);
  **bufp = 0;
  ++*bufp;
}

SWC_CAN_INLINE 
void encode_vstr(uint8_t** bufp, const char* s) {
  encode_vstr(bufp, s, s ? strlen(s) : 0);
}

SWC_CAN_INLINE 
char* decode_vstr(const uint8_t** bufp, size_t* remainp) {
  uint32_t len;
  return decode_vstr(bufp, remainp, &len);
}

SWC_CAN_INLINE 
char* decode_vstr(const uint8_t** bufp, size_t* remainp, uint32_t* lenp) {
  *lenp = decode_vi64(bufp, remainp);
  decode_needed(remainp, *lenp+1);
  char* buf = (char *)*bufp;
  *bufp += *lenp;
  if(**bufp != 0)
    SWC_THROW_OVERRUN("vstr");
  ++*bufp;
  return buf;
}

SWC_CAN_INLINE 
void encode_double(uint8_t** bufp, double val) {
  int64_t lod = (int64_t)val;
  int64_t rod = (int64_t)((val - (double)lod) * (double)1000000000000000000.00);
  encode_i64(bufp, lod);
  encode_i64(bufp, rod);
}

SWC_CAN_INLINE 
double decode_double(const uint8_t** bufp, size_t* remainp) {
  return (double)decode_i64(bufp, remainp) 
       + ((double)decode_i64(bufp, remainp) / (double)1000000000000000000.00);
}

SWC_CAN_INLINE 
int encoded_length_double() {
  return 16;
}

SWC_CAN_INLINE 
bool equal(double a, double b) {
  int64_t lod_a = (int64_t)a;
  int64_t rod_a = (int64_t)((a - (double)lod_a) * (double)1000000000000000000.00);
  double aprime = (double)lod_a + ((double)rod_a / (double)1000000000000000000.00);
  int64_t lod_b = (int64_t)b;
  int64_t rod_b = (int64_t)((b - (double)lod_b) * (double)1000000000000000000.00);
  double bprime = (double)lod_b + ((double)rod_b / (double)1000000000000000000.00);
  return aprime == bprime;
}



}}

# undef SWC_CAN_INLINE 