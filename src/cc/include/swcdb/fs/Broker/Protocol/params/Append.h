/*
 * Copyright Since 2019 SWC-DB© [author: Kashirin Alex kashirin.alex@gmail.com]
 */

#ifndef swc_fs_Broker_Protocol_params_Append_h
#define swc_fs_Broker_Protocol_params_Append_h



namespace SWC { namespace FS { namespace Protocol { namespace Params {


class AppendReq : public Serializable {
  public:

  AppendReq() : fd(-1), flags(0) {}

  AppendReq(int32_t fd, uint8_t flags)
            : fd(fd), flags(flags) {}

  int32_t fd ;
  uint8_t flags;

  private:

  size_t internal_encoded_length() const {
      return 5;
  }

  void internal_encode(uint8_t** bufp) const {
    Serialization::encode_i32(bufp, fd);
    Serialization::encode_i8(bufp, flags);
  }

  void internal_decode(const uint8_t** bufp, size_t* remainp) {
    fd = (int32_t)Serialization::decode_i32(bufp, remainp);
    flags = Serialization::decode_i8(bufp, remainp);
  }
  
};




class AppendRsp : public Serializable {
  public:

  AppendRsp() {}

  AppendRsp(uint64_t offset, uint32_t amount)
           : offset(offset), amount(amount) {}

  uint64_t offset {};
  uint32_t amount {};

  private:

  size_t internal_encoded_length() const {
      return 12;
  }

  void internal_encode(uint8_t** bufp) const {
    Serialization::encode_i64(bufp, offset);
    Serialization::encode_i32(bufp, amount);
  }

  void internal_decode(const uint8_t** bufp, size_t* remainp) {
    offset = Serialization::decode_i64(bufp, remainp);
    amount = Serialization::decode_i32(bufp, remainp);
  }

};

}}}}

#endif // swc_fs_Broker_Protocol_params_Append_h
