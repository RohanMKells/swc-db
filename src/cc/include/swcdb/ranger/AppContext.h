/*
 * SWC-DB© Copyright since 2019 Alex Kashirin <kashirin.alex@gmail.com>
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */

#ifndef swcdb_ranger_AppContext_h
#define swcdb_ranger_AppContext_h


#include "swcdb/core/comm/AppContext.h"
#include "swcdb/core/comm/AppHandler.h"
#include "swcdb/core/comm/ResponseCallback.h"
#include "swcdb/core/comm/DispatchHandler.h"

#include "swcdb/db/client/Clients.h"
#include "swcdb/ranger/RangerEnv.h"

#include "swcdb/db/Protocol/Commands.h"

#include "swcdb/common/Protocol/handlers/NotImplemented.h"
#include "swcdb/ranger/Protocol/Mngr/req/RgrMngId.h"

#include "swcdb/ranger/Protocol/handlers/AssignId.h"
#include "swcdb/ranger/Protocol/handlers/RangeLoad.h"
#include "swcdb/ranger/Protocol/handlers/RangeUnload.h"
#include "swcdb/ranger/Protocol/handlers/RangeIsLoaded.h"
#include "swcdb/ranger/Protocol/handlers/RangeLocate.h"
#include "swcdb/ranger/Protocol/handlers/RangeQueryUpdate.h"
#include "swcdb/ranger/Protocol/handlers/RangeQuerySelect.h"
#include "swcdb/ranger/Protocol/handlers/ColumnUpdate.h"
#include "swcdb/ranger/Protocol/handlers/ColumnDelete.h"
#include "swcdb/ranger/Protocol/handlers/ColumnCompact.h"
#include "swcdb/ranger/Protocol/handlers/Report.h"
#include "swcdb/ranger/Protocol/handlers/ColumnsUnload.h"


namespace SWC { namespace Ranger {



class AppContext final : public Comm::AppContext { 

  // in-order of Comm::Protocol::Rgr::Command
  static constexpr const Comm::AppHandler_t handlers[] = { 
    &Comm::Protocol::Common::Handler::not_implemented,
    &Comm::Protocol::Rgr::Handler::column_delete,
    &Comm::Protocol::Rgr::Handler::column_compact,
    &Comm::Protocol::Rgr::Handler::column_update,
    &Comm::Protocol::Rgr::Handler::range_is_loaded,
    &Comm::Protocol::Rgr::Handler::range_load,
    &Comm::Protocol::Rgr::Handler::range_unload,
    &Comm::Protocol::Rgr::Handler::range_locate,
    &Comm::Protocol::Rgr::Handler::range_query_update,
    &Comm::Protocol::Rgr::Handler::range_query_select,
    &Comm::Protocol::Rgr::Handler::report,
    &Comm::Protocol::Rgr::Handler::columns_unload,
    //&Comm::Protocol::Rgr::Handler::debug,
    //&Comm::Protocol::Rgr::Handler::status,
    //&Comm::Protocol::Rgr::Handler::shutdown
  }; 
  
  public:

  static std::shared_ptr<AppContext> make() {
    auto settings = Env::Config::settings();
    
    settings->parse_file(
      settings->get_str("swc.rgr.cfg", ""),
      "swc.rgr.cfg.dyn"
    );

    Env::IoCtx::init(settings->get_i32("swc.rgr.handlers"));
    
    Env::FsInterface::init(FS::fs_type(settings->get_str("swc.fs")));
      
    Env::Clients::init(
      std::make_shared<client::Clients>(
        Env::IoCtx::io()->shared(),
        std::make_shared<client::ContextManager>(),
        std::make_shared<client::ContextRanger>()
      )
    );
    Env::Rgr::init();

    auto period = settings->get<Config::Property::V_GINT32>(
      "swc.cfg.dyn.period");
    if(period->get()) {
      Env::IoCtx::io()->set_periodic_timer(
        period,
        [](){Env::Config::settings()->check_dynamic_files();}
      );
    }

    auto app = std::make_shared<AppContext>();
    app->id_mngr = std::make_shared<Comm::Protocol::Mngr::Req::RgrMngId>(
      Env::IoCtx::io()->ptr(), 
      [app]() { (new std::thread([app]{ app->stop(); }))->detach(); }
    );
    return app;
  }

  AppContext() 
      : Comm::AppContext(
          Env::Config::settings()->get<Config::Property::V_GENUM>(
            "swc.rgr.comm.encoder")) {
  }

  void init(const Comm::EndPoints& endpoints) override {
    Env::Rgr::rgr_data()->endpoints = endpoints;
    
    int sig = 0;
    Env::IoCtx::io()->set_signals();
    shutting_down(std::error_code(), sig);

    Env::Rgr::start();
    id_mngr->request();
  }

  void set_srv(Comm::server::SerializedServer::Ptr srv){
    m_srv = srv;
  }

  virtual ~AppContext(){}


  void handle(Comm::ConnHandlerPtr conn, const Comm::Event::Ptr& ev) override {

    // SWC_LOGF(LOG_DEBUG, "handle: %s", ev->to_str().c_str());
    
    switch (ev->type) {

      case Comm::Event::Type::ESTABLISHED:
        m_srv->connection_add(conn);
        break; 
        
      case Comm::Event::Type::DISCONNECT:
        m_srv->connection_del(conn);
        break;

      case Comm::Event::Type::ERROR:
        break;

      case Comm::Event::Type::MESSAGE: {
        uint8_t cmd = ev->header.command >= Comm::Protocol::Rgr::MAX_CMD
                        ? (uint8_t)Comm::Protocol::Rgr::NOT_IMPLEMENTED 
                        : ev->header.command;
        
        if(cmd == Comm::Protocol::Rgr::ASSIGN_ID_NEEDED) {
          Comm::Protocol::Rgr::Handler::assign_id(conn, ev, id_mngr);
        
        } else if(!Env::Rgr::rgr_data()->rgrid) {
          try{conn->send_error(Error::RGR_NOT_READY, "", ev);}catch(...){}

        } else {
          Env::IoCtx::post([cmd, conn, ev]() { handlers[cmd](conn, ev); });
        }
        break;
      }

      default:
        SWC_LOGF(LOG_WARN, "Unimplemented event-type (%d)", (int)ev->type);
        break;
    }

  }

  void shutting_down(const std::error_code &ec, const int &sig) {

    if(sig == 0) { // set signals listener
      Env::IoCtx::io()->signals()->async_wait(
        [this](const std::error_code &ec, const int &sig) {
          SWC_LOGF(LOG_INFO, "Received signal, sig=%d ec=%s", 
                   sig, ec.message().c_str());
          shutting_down(ec, sig); 
        }
      ); 
      SWC_LOGF(LOG_INFO, "Listening for Shutdown signal, set at sig=%d ec=%s", 
              sig, ec.message().c_str());
      return;
    }
    SWC_LOGF(LOG_INFO, "Shutdown signal, sig=%d ec=%s", 
             sig, ec.message().c_str());
    
    if(m_srv == nullptr) {
      SWC_LOG(LOG_INFO, "Exit");
      std::quick_exit(0);
    }


    Env::Rgr::shuttingdown();

    m_srv->stop_accepting(); // no further requests accepted

    id_mngr->request();
  }

  void stop() override {
    Env::Rgr::wait_if_in_process();

    Env::Clients::get()->rgr->stop();
    Env::Clients::get()->mngr->stop();
    
    Env::IoCtx::io()->stop();
    Env::FsInterface::interface()->stop();
    
    m_srv->shutdown();

    SWC_LOG(LOG_INFO, "Exit");
    std::quick_exit(0);
  }

  private:
  
  Comm::Protocol::Mngr::Req::RgrMngId::Ptr  id_mngr = nullptr;
  Comm::server::SerializedServer::Ptr       m_srv = nullptr;
  
};


}}



#endif // swcdb_ranger_AppContext_h
