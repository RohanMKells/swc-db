/*
 * SWC-DB© Copyright since 2019 Alex Kashirin <kashirin.alex@gmail.com>
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */


#include "swcdb/core/comm/HeaderBufferInfo.h"


namespace SWC { namespace Comm {



void BufferInfo::encode(Core::Encoder::Type _enc, StaticBuffer& data) {
  if(_enc != Core::Encoder::Type::PLAIN &&
     encoder == Core::Encoder::Type::PLAIN &&
     data.size > 32) { // at least size if encoder not encrypt-type

    int err = Error::OK;
    size_t len_enc = 0;
    DynamicBuffer output;
    Core::Encoder::encode(err, _enc, data.base, data.size,
                          &len_enc, output, 0, true);
    if(len_enc) {
      encoder = _enc;
      size_plain = data.size;
      data.set(output);
    }
  }

  size   = data.size;
  chksum = Core::checksum32(data.base, data.size);
}

void BufferInfo::decode(int& err, StaticBuffer& data) const {
  if(size_plain) {
    StaticBuffer decoded_buf(static_cast<size_t>(size_plain));
    Core::Encoder::decode(
      err, encoder,
      data.base, data.size,
      decoded_buf.base, size_plain
    );
    if(!err)
      data.set(decoded_buf);
  }
}

void BufferInfo::print(std::ostream& out) const {
  out << " Buffer(sz=" << size
      << " enc=" << Core::Encoder::to_string(encoder)
      << " szplain=" << size_plain
      << " chk=" << chksum << ')';
}


}}
