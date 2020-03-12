/*
 * Copyright Since 2019 SWC-DB© [author: Kashirin Alex kashirin.alex@gmail.com]
 */

#ifndef swc_core_Encoder_h
#define swc_core_Encoder_h

#include "swcdb/db/Types/Encoding.h"

namespace SWC { namespace Encoder {


void decode(int& err, Types::Encoding encoder, 
            const uint8_t* src, size_t sz_enc, 
            uint8_t *dst, size_t sz);

void encode(int& err, Types::Encoding encoder, 
            const uint8_t* src, size_t src_sz, 
            size_t* sz_enc, DynamicBuffer& output, 
            uint32_t reserve);

}}


#ifdef SWC_IMPL_SOURCE
#include "swcdb/core/Encoder.cc"
#endif 


#endif // swc_core_Encoder_h
