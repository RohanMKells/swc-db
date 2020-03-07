
/*
 * Copyright (C) 2019 SWC-DB (author: Kashirin Alex (kashirin.alex@gmail.com))
 */ 

#ifndef swc_lib_db_protocol_req_RgrUpdate_h
#define swc_lib_db_protocol_req_RgrUpdate_h

#include "swcdb/db/Protocol/Mngr/params/RgrUpdate.h"

namespace SWC { namespace Protocol { namespace Mngr { namespace Req {


class RgrUpdate : public client::ConnQueue::ReqBase {
  public:

  RgrUpdate(server::Mngr::RangerList &hosts, bool sync_all) {
    cbp = CommBuf::make(Params::RgrUpdate(hosts, sync_all));
    cbp->header.set(RGR_UPDATE, 60000);
  }
  
  virtual ~RgrUpdate() { }

  void handle(ConnHandlerPtr conn, Event::Ptr& ev) override {
    if(was_called || !is_rsp(conn, ev))
      return;

    if(ev->header.command == RGR_UPDATE 
      && ev->response_code() == Error::OK){
      was_called = true;
      return;
    }

    conn->do_close();
  }

};

}}}}

#endif // swc_lib_db_protocol_mngr_req_RgrUpdate_h
