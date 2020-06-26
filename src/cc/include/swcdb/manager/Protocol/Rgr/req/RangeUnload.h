
/*
 * Copyright Since 2019 SWC-DB© [author: Kashirin Alex kashirin.alex@gmail.com]
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */ 

#ifndef swc_manager_Protocol_rgr_req_RangeUnload_h
#define swc_manager_Protocol_rgr_req_RangeUnload_h



namespace SWC { namespace Protocol { namespace Rgr { namespace Req {


class RangeUnload : public client::ConnQueue::ReqBase {
  public:

  RangeUnload(const Manager::Range::Ptr& range, 
              const ResponseCallback::Ptr& cb,
              uint32_t timeout=60000);

  virtual ~RangeUnload();

  void handle(ConnHandlerPtr conn, const Event::Ptr& ev) override;

  bool valid() override;
  
  void handle_no_conn() override;

  void unloaded(int err, const ResponseCallback::Ptr& cb);

  private:

  ResponseCallback::Ptr cb;
  Manager::Range::Ptr   range;
   
};

}}}}

#endif // swc_manager_Protocol_rgr_req_RangeUnload_h
