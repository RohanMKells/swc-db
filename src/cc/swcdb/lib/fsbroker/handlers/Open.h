/*
 * Copyright (C) 2019 SWC-DB (author: Kashirin Alex (kashirin.alex@gmail.com))
 */


#ifndef swc_app_fsbroker_handlers_Open_h
#define swc_app_fsbroker_handlers_Open_h

#include "swcdb/lib/fs/Broker/Protocol/params/Open.h"


namespace SWC { namespace server { namespace FsBroker {

namespace Handler {


class Open : public AppHandler {
  public:

  Open(ConnHandlerPtr conn, Event::Ptr ev)
         : AppHandler(conn, ev){ }

  void run() override {

    int err = Error::OK;
    int32_t fd = -1;

    try {

      const uint8_t *ptr = m_ev->data.base;
      size_t remain = m_ev->data.size;

      FS::Protocol::Params::OpenReq params;
      params.decode(&ptr, &remain);

      FS::SmartFdPtr smartfd 
        = FS::SmartFd::make_ptr(params.get_name(), params.get_flags());
 
      Env::FsInterface::fs()->open(err, smartfd, params.get_buffer_size());
      
      if(smartfd->valid() && err==Error::OK)
        fd = Env::Fds::get()->add(smartfd);
    }
    catch (Exception &e) {
      HT_ERROR_OUT << e << HT_END;
      err = e.code();
    }
  
    try {
      CommHeader header;
      header.initialize_from_request_header(m_ev->header);
      auto cbp = CommBuf::make(header, FS::Protocol::Params::OpenRsp(fd), 4);
      cbp->append_i32(err);
      cbp->finalize_data();
      m_conn->send_response(cbp);
    }
    catch (Exception &e) {
      HT_ERROR_OUT << e << HT_END;
    }

  }

};
  

}}}}

#endif // swc_app_fsbroker_handlers_Open_h