/*
 * SWC-DB© Copyright since 2019 Alex Kashirin <kashirin.alex@gmail.com>
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */


#ifndef swc_db_Protocol_handlers_NotImplemented_h
#define swc_db_Protocol_handlers_NotImplemented_h


namespace SWC { namespace Protocol {  namespace Common { namespace Handler {

void not_implemented(const ConnHandlerPtr& conn, const Event::Ptr& ev) {
    try {
      auto cbp = CommBuf::make(4);
      cbp->header.initialize_from_request_header(ev->header);
      cbp->append_i32(Error::NOT_IMPLEMENTED);
      conn->send_response(cbp);

    } catch (...) {
      SWC_LOG_CURRENT_EXCEPTION("");
    }
}


class NotImplemented : public AppHandler {
  public:

  NotImplemented(const ConnHandlerPtr& conn, const Event::Ptr& ev)
                : AppHandler(conn, ev){
  }

  void run() override {
    not_implemented(m_conn, m_ev);
  }

};
  

}}}}

#endif // swc_db_Protocol_handlers_NotImplemented_h