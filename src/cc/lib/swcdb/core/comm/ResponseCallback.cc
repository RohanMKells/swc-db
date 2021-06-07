/*
 * SWC-DB© Copyright since 2019 Alex Kashirin <kashirin.alex@gmail.com>
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */


#include "swcdb/core/comm/ResponseCallback.h"


namespace SWC { namespace Comm {


bool ResponseCallback::expired(int64_t within) const noexcept {
  return  (m_ev != nullptr && m_ev->expired(within)) ||
          (m_conn != nullptr && !m_conn->is_open());
}

void ResponseCallback::response(int& err) {
  err ? send_error(err, "") : response_ok();
}


}}
