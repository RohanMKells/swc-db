/*
 * Copyright Since 2019 SWC-DB© [author: Kashirin Alex kashirin.alex@gmail.com]
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */


#ifndef swc_fsbroker_handlers_Read_h
#define swc_fsbroker_handlers_Read_h

#include "swcdb/fs/Broker/Protocol/params/Read.h"


namespace SWC { namespace FsBroker { namespace Handler {


void read(const ConnHandlerPtr& conn, const Event::Ptr& ev) {

  int err = Error::OK;
  size_t offset = 0;
  StaticBuffer rbuf;
  try {

    const uint8_t *ptr = ev->data.base;
    size_t remain = ev->data.size;

    FS::Protocol::Params::ReadReq params;
    params.decode(&ptr, &remain);

    auto smartfd = Env::Fds::get()->select(params.fd);
      
    if(!smartfd) {
      err = EBADR;
    } else {
      offset = smartfd->pos();
      rbuf.reallocate(params.amount);
      rbuf.size = Env::FsInterface::fs()->read(
        err, smartfd, rbuf.base, params.amount);
    }

  } catch (Exception &e) {
    SWC_LOG_OUT(LOG_ERROR) << e << SWC_LOG_OUT_END;
    err = e.code();
  }
  
  if(ev->expired())
    return;

  try {
    auto cbp = CommBuf::make(FS::Protocol::Params::ReadRsp(offset), rbuf, 4);
    cbp->header.initialize_from_request_header(ev->header);
    cbp->append_i32(err);
    conn->send_response(cbp);

  } catch (Exception &e) {
    SWC_LOG_OUT(LOG_ERROR) << e << SWC_LOG_OUT_END;
  }

}


}}}

#endif // swc_fsbroker_handlers_Read_h