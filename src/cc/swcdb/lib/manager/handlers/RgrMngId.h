/*
 * Copyright (C) 2019 SWC-DB (author: Kashirin Alex (kashirin.alex@gmail.com))
 */


#ifndef swc_app_manager_handlers_RgrMngId_h
#define swc_app_manager_handlers_RgrMngId_h

#include "swcdb/lib/db/Protocol/Mngr/params/RgrMngId.h"


namespace SWC { namespace Protocol { namespace Mngr { namespace Handler {


class RgrMngId : public AppHandler {
  public:

    RgrMngId(ConnHandlerPtr conn, Event::Ptr ev)
            : AppHandler(conn, ev){}

  void run() override {

    try {

      const uint8_t *ptr = m_ev->data.base;
      size_t remain = m_ev->data.size;

      Params::RgrMngId req_params;
      req_params.decode(&ptr, &remain);

      // ResponseCallback::Ptr cb = 
      //  std::make_shared<ResponseCallback>(m_conn, m_ev);
      
      
      if(!Env::MngrRole::get()->is_active(1)){
        HT_DEBUGF("MNGR NOT ACTIVE, flag=%d id=%d %s",
                  req_params.flag, req_params.id, 
                  req_params.to_string().c_str());
        
        CommHeader header;
        header.initialize_from_request_header(m_ev->header);
        auto cbp = CommBuf::make(
          header, 
          Params::RgrMngId(0, Params::RgrMngId::Flag::MNGR_NOT_ACTIVE)
        );
        m_conn->send_response(cbp);
        return;
      }

      server::Mngr::RangersPtr rangers = Env::Rangers::get();
      switch(req_params.flag){

        case Params::RgrMngId::Flag::RS_REQ: {
          uint64_t id = rangers->rs_set_id(req_params.endpoints);

          HT_DEBUGF("RS_REQ, id=%d %s",
                    req_params.id, req_params.to_string().c_str());

          CommHeader header;
          header.initialize_from_request_header(m_ev->header);
          auto cbp = CommBuf::make(
            header, 
            Params::RgrMngId(id, Params::RgrMngId::Flag::MNGR_ASSIGNED)
          );
          m_conn->send_response(cbp);
          break;
        }

        case Params::RgrMngId::Flag::RS_ACK: {
          if(rangers->rs_ack_id(req_params.id, req_params.endpoints)){
            HT_DEBUGF("RS_ACK, id=%d %s",
                      req_params.id, req_params.to_string().c_str());
            m_conn->response_ok(m_ev);

          } else {
            HT_DEBUGF("RS_ACK(MNGR_REREQ) id=%d %s",
                      req_params.id, req_params.to_string().c_str());
            
            CommHeader header;
            header.initialize_from_request_header(m_ev->header);
            auto cbp = CommBuf::make(
              header, 
              Params::RgrMngId(0, Params::RgrMngId::Flag::MNGR_REREQ)
            );
            m_conn->send_response(cbp);
          }
          break;
        }

        case Params::RgrMngId::Flag::RS_DISAGREE: {
          uint64_t id = rangers->rs_had_id(req_params.id, 
                                                   req_params.endpoints);
          HT_DEBUGF("RS_DISAGREE, rs_had_id=%d > id=%d %s", 
                    req_params.id, id, req_params.to_string().c_str());

          if (id != 0){
      
            CommHeader header;
            header.initialize_from_request_header(m_ev->header);
            auto cbp = CommBuf::make(
              header, 
              Params::RgrMngId(id, Params::RgrMngId::Flag::MNGR_REASSIGN)
            );
            m_conn->send_response(cbp);
          } else {
            m_conn->response_ok(m_ev);
          }

          break;
        }

        case Params::RgrMngId::Flag::RS_SHUTTINGDOWN: {
          rangers->rs_shutdown(req_params.id, req_params.endpoints);

          HT_DEBUGF("RS_SHUTTINGDOWN, id=%d %s",
                    req_params.id, req_params.to_string().c_str());
      
          CommHeader header;
          header.initialize_from_request_header(m_ev->header);
          auto cbp = CommBuf::make(
            header, 
            Params::RgrMngId(
              req_params.id, Params::RgrMngId::Flag::RS_SHUTTINGDOWN)
          );
          m_conn->send_response(cbp);
          break;
        }
        
        default:
          break;
      }

    } catch (Exception &e) {
      HT_ERROR_OUT << e << HT_END;
    }
    
  }

};
  

}}}}

#endif // swc_app_manager_handlers_RgrMngId