/*
 * Copyright Since 2019 SWC-DB© [author: Kashirin Alex kashirin.alex@gmail.com]
 * Copyright (C) 2007-2016 Hypertable, Inc.
 *
 * This file is part of Hypertable.
 *
 * Hypertable is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or any later version.
 *
 * Hypertable is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Hypertable. If not, see <http://www.gnu.org/licenses/>
 */


#include "swcdb/core/String.h"
#include "swcdb/core/Compat.h"

#include <cstdarg>
#include <cstdio>
#include <algorithm>


namespace SWC {

std::string format(const char *fmt, ...) {
  char buf[1024];       // should be enough for most cases
  int n, size = sizeof(buf);
  char *p = buf;
  va_list ap;

  do {
    va_start(ap, fmt);
    n = vsnprintf(p, size, fmt, ap);
    va_end(ap);

    if (n > -1 && n < size)
      break;    // worked!

    if (n > -1)         // glibc 2.1+/iso c99
      size = n + 1;     //   exactly what's needed
    else                // glibc 2.0
      size *= 2;        //   double the size and try again

    p = (char *)(p == buf ? malloc(size) : realloc(p, size));

    if (!p)
      throw std::bad_alloc();
  } while (true);

  if (buf == p)
    return std::string(p, n);

  std::string ret(p, n);
  free(p);

  return ret;
}


} // namespace SWC
