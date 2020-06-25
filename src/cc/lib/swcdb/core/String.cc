/*
 * Copyright Since 2019 SWC-DB© [author: Kashirin Alex kashirin.alex@gmail.com]
 */


#include "swcdb/core/String.h"
#include "swcdb/core/Compat.h"

#include <cstdarg>
#include <cstdio>


namespace SWC {


std::string format(const char *fmt, ...) {
  std::string res;
  
  std::va_list ap1; 
  std::va_list ap2; 
  va_start(ap1, fmt);
  va_copy(ap2, ap1);
  
  res.resize(std::vsnprintf(nullptr, 0, fmt, ap1));
  std::vsnprintf(res.data(), res.size() + 1, fmt, ap2);
  
  va_end(ap1);
  va_end(ap2);
  return res;
}


} // namespace SWC
