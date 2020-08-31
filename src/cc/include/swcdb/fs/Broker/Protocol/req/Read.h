/*
 * Copyright Since 2019 SWC-DB© [author: Kashirin Alex kashirin.alex@gmail.com]
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */

#ifndef swc_fs_Broker_Protocol_req_Read_h
#define swc_fs_Broker_Protocol_req_Read_h

#include "swcdb/fs/Broker/Protocol/req/Base.h"
#include "swcdb/fs/Broker/Protocol/params/Read.h"

namespace SWC { namespace FS { namespace Protocol { namespace Req {

class Read : public Base {

  public:
  
  void*   buffer;
  bool    allocated;
  size_t  amount;
  
  Read(uint32_t timeout, SmartFd::Ptr& smartfd, void* dst, size_t len, 
       bool allocated, const Callback::ReadCb_t& cb=0);

  std::promise<void> promise();

  void handle(ConnHandlerPtr, const Event::Ptr& ev) override;

  private:
  SmartFd::Ptr        smartfd;
  Callback::ReadCb_t  cb;

};



}}}}


#ifdef SWC_IMPL_SOURCE
#include "swcdb/fs/Broker/Protocol/req/Read.cc"
#endif 

#endif  // swc_fs_Broker_Protocol_req_Read_h
