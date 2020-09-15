
/*
 * SWC-DB© Copyright since 2019 Alex Kashirin <kashirin.alex@gmail.com>
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */ 

#ifndef swc_ranger_protocol_rgr_req_RangeUnload_h
#define swc_ranger_protocol_rgr_req_RangeUnload_h



namespace SWC { namespace Protocol { namespace Rgr { namespace Req {


class RangeUnload : public client::ConnQueue::ReqBase {
  public:

  RangeUnload(const Ranger::RangePtr& range, 
              const ResponseCallback::Ptr& cb,
              uint32_t timeout=60000);

  virtual ~RangeUnload();

  void handle(ConnHandlerPtr conn, const Event::Ptr& ev) override;

  bool valid() override;
  
  void handle_no_conn() override;

  void unloaded(int err);

  private:

  ResponseCallback::Ptr cb;
  Ranger::RangePtr      range;
   
};

}}}}

#endif // swc_ranger_protocol_rgr_req_RangeUnload_h
