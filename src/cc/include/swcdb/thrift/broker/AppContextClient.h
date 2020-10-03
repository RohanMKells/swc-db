/*
 * SWC-DB© Copyright since 2019 Alex Kashirin <kashirin.alex@gmail.com>
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */

#ifndef swcdb_ThriftBroker_AppContextClient_h
#define swcdb_ThriftBroker_AppContextClient_h


namespace SWC { namespace client { 


//! The SWC-DB ThriftBroker's Client to Database C++ namespace 'SWC::client::ThriftBroker'
namespace ThriftBroker {


class AppContext final : public Comm::AppContext {
  public:

  AppContext() {}
  virtual ~AppContext(){}

  void disconnected(const Comm::ConnHandlerPtr&) {};

  void handle(Comm::ConnHandlerPtr conn, const Comm::Event::Ptr& ev) override {
    
    switch (ev->type) {

      case Comm::Event::Type::DISCONNECT: {
        disconnected(conn);
        return;
      }

      case Comm::Event::Type::MESSAGE:
      case Comm::Event::Type::ERROR: {
        SWC_LOG_OUT(LOG_WARN,  ev->print(SWC_LOG_OSTREAM << "unhandled: "); );
        break;
      }

      case Comm::Event::Type::ESTABLISHED:
      default: {
        break;
      }

    }
    
  
  }
  
};

}}}

#endif // swcdb_ThriftBroker_AppContextClient_h