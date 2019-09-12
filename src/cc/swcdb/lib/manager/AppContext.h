/*
 * Copyright (C) 2019 SWC-DB (author: Kashirin Alex (kashirin.alex@gmail.com))
 */

#ifndef swc_app_manager_AppContext_h
#define swc_app_manager_AppContext_h

#include "swcdb/lib/db/Protocol/Commands.h"

#include "swcdb/lib/core/comm/AppContext.h"
#include "swcdb/lib/core/comm/AppHandler.h"
#include "swcdb/lib/core/comm/ResponseCallback.h"
#include "swcdb/lib/core/comm/DispatchHandler.h"

#include "swcdb/lib/fs/Interface.h"
#include "swcdb/lib/client/Clients.h"

#include "swcdb/lib/db/Columns/Schema.h"
#include "swcdb/lib/db/Columns/MNGR/Columns.h"

#include "MngrRole.h"
#include "RangeServers.h"

#include "swcdb/lib/db/Protocol/handlers/NotImplemented.h"
#include "swcdb/lib/db/Protocol/handlers/Echo.h"
#include "handlers/MngrsState.h"
#include "handlers/ActiveMngr.h"
#include "handlers/RsMngId.h"
#include "handlers/UpdateRangeServers.h"
#include "handlers/ColumnMng.h"
#include "handlers/ColumnGet.h"
#include "handlers/ColumnUpdate.h"


namespace SWC { namespace server { namespace Mngr {


class AppContext : public SWC::AppContext {
  
  public:

  AppContext() {
    Env::Config::settings()->parse_file(
      Env::Config::settings()->get<String>("swc.mngr.cfg", ""),
      Env::Config::settings()->get<String>("swc.mngr.OnFileChange.cfg", "")
    );

    Env::IoCtx::init(
      Env::Config::settings()->get<int32_t>("swc.mngr.handlers"));
    Env::MngrRole::init();
    Env::FsInterface::init();
    Env::Schemas::init();
    Env::MngrColumns::init();
    Env::Clients::init(std::make_shared<client::Clients>(
      Env::IoCtx::io()->shared(),
      std::make_shared<client::Mngr::AppContext>()
    ));
    Env::RangeServers::init();
  }
  
  void init(const EndPoints& endpoints) override {
    Env::MngrRole::get()->init(endpoints);
    
    int sig = 0;
    Env::IoCtx::io()->set_signals();
    shutting_down(std::error_code(), sig);
  }

  void set_srv(SerializedServerPtr srv){
    m_srv = srv;
  }

  virtual ~AppContext(){}


  void handle(ConnHandlerPtr conn, EventPtr ev) override {
    // HT_DEBUGF("handle: %s", ev->to_str().c_str());

    switch (ev->type) {

      case Event::Type::CONNECTION_ESTABLISHED:
        m_srv->connection_add(conn);
        return; 
        
      case Event::Type::DISCONNECT:
        m_srv->connection_del(conn);
        if(Env::MngrRole::get()->disconnection(
                          conn->endpoint_remote, conn->endpoint_local, true))
          return;
        return;

      case Event::Type::ERROR:
        //rangeservers->decommision(event->addr);
        break;

      case Event::Type::MESSAGE: {
        AppHandler *handler = 0;
        switch (ev->header.command) {

          case Protocol::Command::MNGR_REQ_MNGRS_STATE:
            handler = new Handler::MngrsState(conn, ev);
            break;

          case Protocol::Command::MNGR_UPDATE_RANGESERVERS:
            handler = new Handler::UpdateRangeServers(conn, ev);
            break;

          case Protocol::Command::CLIENT_REQ_ACTIVE_MNGR:
            handler = new Handler::ActiveMngr(conn, ev);
            break;

          case Protocol::Command::REQ_MNGR_MNG_RS_ID:
            handler = new Handler::RsMngId(conn, ev);
            break;

          case Protocol::Command::CLIENT_REQ_MNG_COLUMN:
            handler = new Handler::ColumnMng(conn, ev);
            break;

          case Protocol::Command::CLIENT_REQ_GET_COLUMN:
            handler = new Handler::ColumnGet(conn, ev);
            break;

          case Protocol::Command::MNGR_UPDATE_COLUMN:
            handler = new Handler::ColumnUpdate(conn, ev);
            break;

          case Protocol::Command::REQ_ECHO:
            handler = new common::Handler::Echo(conn, ev);
            break;

          // + MngrRsResource
          

          case Protocol::Command::CLIENT_REQ_RS_ADDR:
            //rangeservers->get_addr(event);
            break;

          case Protocol::Command::CLIENT_REQ_CID_NAME:
            //columns->get_cid_of_name(event);
            break;

          default: 
            handler = new common::Handler::NotImplemented(conn, ev);
            break;
        }

        if(handler)
          asio::post(*Env::IoCtx::io()->ptr(), 
                    [hdlr=AppHandlerPtr(handler)](){ hdlr->run();  });

        break;
      }

      default:
        HT_WARNF("Unimplemented event-type (%llu)", (Llu)ev->type);
        break;

    }
  }
  
  void shutting_down(const std::error_code &ec, const int &sig) {

    if(sig==0){ // set signals listener
      Env::IoCtx::io()->signals()->async_wait(
        [ptr=this](const std::error_code &ec, const int &sig){
          HT_INFOF("Received signal, sig=%d ec=%s", sig, ec.message().c_str());
          ptr->shutting_down(ec, sig); 
        }
      ); 
      HT_INFOF("Listening for Shutdown signal, set at sig=%d ec=%s", 
              sig, ec.message().c_str());
      return;
    }

    HT_INFOF("Shutdown signal, sig=%d ec=%s", sig, ec.message().c_str());
    
    (new std::thread([ptr=shared_from_this()]{ ptr->stop(); }))->detach();
  }

  void stop() override {
    
    m_srv->stop_accepting(); // no further requests accepted
    
    Env::RangeServers::get()->stop();
    Env::MngrRole::get()->stop();

    Env::Clients::get()->rs_service->stop();
    Env::Clients::get()->mngr_service->stop();

    Env::FsInterface::interface()->stop();
    
    Env::IoCtx::io()->stop();
    
    m_srv->shutdown();
    
    HT_INFO("Exit");
    std::quick_exit(0);
  }

  private:
  SerializedServerPtr m_srv = nullptr;
  //ColmNameToIDMap columns;       // column-name > CID


};

}}}

#endif // swc_app_manager_AppContext_h