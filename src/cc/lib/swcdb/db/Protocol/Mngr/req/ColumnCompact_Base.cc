/*
 * SWC-DB© Copyright since 2019 Alex Kashirin <kashirin.alex@gmail.com>
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */


#include "swcdb/db/Protocol/Mngr/req/MngrActive.h"
#include "swcdb/db/Protocol/Mngr/req/ColumnCompact_Base.h"
#include "swcdb/db/Protocol/Commands.h"


namespace SWC { namespace Comm { namespace Protocol {
namespace Mngr { namespace Req {



void ColumnCompact_Base::handle_no_conn() {
  if(get_clients()->stopping()) {
    callback(Params::ColumnCompactRsp(Error::CLIENT_STOPPING));
  } else if(!valid()) {
    callback(Params::ColumnCompactRsp(Error::CANCELLED));
  } else {
    get_clients()->remove_mngr(endpoints);
    endpoints.clear();
    run();
  }
}

bool ColumnCompact_Base::run() {
  if(endpoints.empty()) {
    get_clients()->get_mngr(cid, endpoints);
    if(endpoints.empty()) {
      if(get_clients()->stopping()) {
        callback(Params::ColumnCompactRsp(Error::CLIENT_STOPPING));
      } else if(!valid()) {
        callback(Params::ColumnCompactRsp(Error::CANCELLED));
      } else {
        MngrActive::make(get_clients(), cid, shared_from_this())->run();
      }
      return false;
    }
  }
  get_clients()->get_mngr_queue(endpoints)->put(req());
  return true;
}

void ColumnCompact_Base::handle(ConnHandlerPtr, const Event::Ptr& ev) {
  Params::ColumnCompactRsp rsp(ev->error);
  if(!rsp.err) {
    try {
      const uint8_t *ptr = ev->data.base;
      size_t remain = ev->data.size;
      rsp.decode(&ptr, &remain);

    } catch(...) {
      const Error::Exception& e = SWC_CURRENT_EXCEPTION("");
      SWC_LOG_OUT(LOG_ERROR, SWC_LOG_OSTREAM << e; );
      rsp.err = e.code();
    }
  }
  callback(rsp);
}



}}}}}
