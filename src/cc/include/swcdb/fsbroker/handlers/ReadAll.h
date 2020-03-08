/*
 * Copyright (C) 2019 SWC-DB (author: Kashirin Alex (kashirin.alex@gmail.com))
 */


#ifndef swc_fsbroker_handlers_ReadAll_h
#define swc_fsbroker_handlers_ReadAll_h

#include "swcdb/fs/Broker/Protocol/params/ReadAll.h"


namespace SWC { namespace FsBroker { namespace Handler {


void read_all(ConnHandlerPtr conn, Event::Ptr ev) {

  int err = Error::OK;
  size_t offset = 0;
  StaticBuffer rbuf;
  try {

    const uint8_t *ptr = ev->data.base;
    size_t remain = ev->data.size;

    FS::Protocol::Params::ReadAllReq params;
    params.decode(&ptr, &remain);

    Env::FsInterface::fs()->read(err, params.name, &rbuf);

  } catch (Exception &e) {
    SWC_LOG_OUT(LOG_ERROR) << e << SWC_LOG_OUT_END;
    err = e.code();
  }
  
  if(ev->expired())
    return;

  try {
    auto cbp = err ? CommBuf::make(4) : CommBuf::make(rbuf, 4); 
    cbp->header.initialize_from_request_header(ev->header);
    cbp->append_i32(err);
    conn->send_response(cbp);
  }
  catch (Exception &e) {
    SWC_LOG_OUT(LOG_ERROR) << e << SWC_LOG_OUT_END;
  }

}


}}}

#endif // swc_fsbroker_handlers_ReadAll_h