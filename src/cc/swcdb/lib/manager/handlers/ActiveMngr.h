/*
 * Copyright (C) 2019 SWC-DB (author: Kashirin Alex (kashirin.alex@gmail.com))
 */


#ifndef swc_app_manager_handlers_ActiveMngr_h
#define swc_app_manager_handlers_ActiveMngr_h

#include "swcdb/lib/db/Protocol/params/ActiveMngr.h"


namespace SWC { namespace server { namespace Mngr {

namespace Handler {


class ActiveMngr : public AppHandler {
  public:

  ActiveMngr(ConnHandlerPtr conn, EventPtr ev)
            : AppHandler(conn, ev){ }

  void run() override {

    try {

      const uint8_t *ptr = m_ev->payload;
      size_t remain = m_ev->payload_len;

      Protocol::Params::ActiveMngrReq params;
      const uint8_t *base = ptr;
      params.decode(&ptr, &remain);

      MngrStatusPtr h = Env::MngrRoleState::get()->active_mngr(
        params.begin, params.end);

      EndPoints endpoints;
      if(h!=nullptr) 
        endpoints = h->endpoints;
      Protocol::Params::ActiveMngrRsp rsp_params(endpoints);
      
      CommHeader header;
      header.initialize_from_request_header(m_ev->header);
      CommBufPtr cbp = std::make_shared<CommBuf>(
        header, rsp_params.encoded_length());
      rsp_params.encode(cbp->get_data_ptr_address());

      m_conn->send_response(cbp);
      
    }
    catch (Exception &e) {
      HT_ERROR_OUT << e << HT_END;
    }
  
  }

};
  

}}}}

#endif // swc_app_manager_handlers_ActiveMngr_h