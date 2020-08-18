
/*
 * Copyright Since 2019 SWC-DB© [author: Kashirin Alex kashirin.alex@gmail.com]
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */ 

#ifndef swc_manager_Protocol_rgr_req_RangeUnload_h
#define swc_manager_Protocol_rgr_req_RangeUnload_h



namespace SWC { namespace Protocol { namespace Rgr { namespace Req {


class RangeUnload : public client::ConnQueue::ReqBase {
  public:

  RangeUnload(const Manager::Ranger::Ptr& rgr,
              const Manager::Column::Ptr& col, 
              const Manager::Range::Ptr& range,
              uint32_t timeout=60000);

  virtual ~RangeUnload();

  bool valid() override;

  void handle(ConnHandlerPtr conn, const Event::Ptr& ev) override;

  void handle_no_conn() override;

  void unloaded(int err);

  private:
  
  const Manager::Ranger::Ptr rgr;
  const Manager::Column::Ptr col;
  const Manager::Range::Ptr  range;
   
};

}}}}

#endif // swc_manager_Protocol_rgr_req_RangeUnload_h
