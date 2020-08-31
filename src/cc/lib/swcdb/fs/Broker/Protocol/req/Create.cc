/*
 * Copyright Since 2019 SWC-DB© [author: Kashirin Alex kashirin.alex@gmail.com]
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */


#include "swcdb/fs/Broker/Protocol/req/Create.h"


namespace SWC { namespace FS { namespace Protocol { namespace Req {


Create::Create(FileSystem::Ptr fs, uint32_t timeout, SmartFd::Ptr& smartfd, 
               int32_t bufsz, uint8_t replication, int64_t blksz, 
               const Callback::CreateCb_t& cb) 
              : fs(fs), smartfd(smartfd), cb(cb) {
  SWC_LOGF(LOG_DEBUG, 
    "create %s bufsz(%d) replication(%d) blksz(%ld)", 
    smartfd->to_string().c_str(), bufsz, replication, blksz);
  
  cbp = CommBuf::make(
    Params::CreateReq(smartfd->filepath(), smartfd->flags(), 
                      bufsz, replication, blksz)
  );
  cbp->header.set(Cmd::FUNCTION_CREATE, timeout);
}

std::promise<void> Create::promise() {
  std::promise<void>  r_promise;
  cb = [await=&r_promise](int, const SmartFd::Ptr&){ await->set_value(); };
  return r_promise;
}

void Create::handle(ConnHandlerPtr, const Event::Ptr& ev) { 

  const uint8_t *ptr;
  size_t remain;

  if(!Base::is_rsp(ev, Cmd::FUNCTION_CREATE, &ptr, &remain))
    return;

  if(!error) {
    Params::OpenRsp params;
    params.decode(&ptr, &remain);
    smartfd->fd(params.fd);
    smartfd->pos(0);
    fs->fd_open_incr();
  }

  SWC_LOGF(LOG_DEBUG, "create %s error='%d' fds-open=%lu", 
           smartfd->to_string().c_str(), error, fs->fds_open());
  
  cb(error, smartfd);
}



}}}}
