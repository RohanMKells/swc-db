
/*
 * Copyright Since 2019 SWC-DB© [author: Kashirin Alex kashirin.alex@gmail.com]
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */ 

#ifndef swc_manager_Protocol_mngr_req_MngrState_h
#define swc_manager_Protocol_mngr_req_MngrState_h

#include "swcdb/manager/Protocol/Mngr/params/MngrState.h"
 
namespace SWC { namespace Protocol { namespace Mngr {namespace Req {


class MngrState : public client::ConnQueue::ReqBase {
  public:

  MngrState(const ResponseCallback::Ptr& cb, 
            const Manager::MngrsStatus& states, 
            uint64_t token, const EndPoint& mngr_host, 
            uint32_t timeout);
  
  virtual ~MngrState();

  void disconnected(const ConnHandlerPtr& conn);

  void handle(ConnHandlerPtr conn, const Event::Ptr& ev) override;

  private:
  ResponseCallback::Ptr   cb;
};

}}}}

#endif // swc_manager_Protocol_mngr_req_MngrState_h
