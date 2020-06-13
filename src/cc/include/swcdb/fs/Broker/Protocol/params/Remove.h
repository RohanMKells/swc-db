/*
 * Copyright Since 2019 SWC-DB© [author: Kashirin Alex kashirin.alex@gmail.com]
 */

#ifndef swc_fs_Broker_Protocol_params_Remove_h
#define swc_fs_Broker_Protocol_params_Remove_h



namespace SWC { namespace FS { namespace Protocol { namespace Params {


class RemoveReq : public Serializable {
  public:

  RemoveReq() {}

  RemoveReq(const std::string& fname) : fname(fname) {}

  std::string fname;

  private:

  uint8_t encoding_version() const {
    return 1; 
  }

  size_t encoded_length_internal() const override {
  return Serialization::encoded_length_vstr(fname);
  }

  void encode_internal(uint8_t **bufp) const override {
    Serialization::encode_vstr(bufp, fname);
  }

  void decode_internal(uint8_t version, const uint8_t **bufp,
                       size_t *remainp) override {
    (void)version;
    fname.clear();
    fname.append(Serialization::decode_vstr(bufp, remainp));
  }

};

}}}}

#endif // swc_fs_Broker_Protocol_params_Remove_h
