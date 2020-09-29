/*
 * SWC-DB© Copyright since 2019 Alex Kashirin <kashirin.alex@gmail.com>
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */


#include "swcdb/fs/Broker/Protocol/req/Mkdirs.h"


namespace SWC { namespace FS { namespace Protocol { namespace Req {


Mkdirs::Mkdirs(uint32_t timeout, const std::string& name, 
               const Callback::MkdirsCb_t& cb) 
              : name(name), cb(cb) {
  SWC_LOGF(LOG_DEBUG, "mkdirs path='%s'", name.c_str());

  cbp = Comm::CommBuf::make(Params::MkdirsReq(name));
  cbp->header.set(Cmd::FUNCTION_MKDIRS, timeout);
}

std::promise<void> Mkdirs::promise() {
  std::promise<void>  r_promise;
  cb = [await=&r_promise](int){ await->set_value(); };
  return r_promise;
}

void Mkdirs::handle(Comm::ConnHandlerPtr, const Comm::Event::Ptr& ev) { 

  const uint8_t *ptr;
  size_t remain;

  if(!Base::is_rsp(ev, Cmd::FUNCTION_MKDIRS, &ptr, &remain))
    return;

  SWC_LOGF(LOG_DEBUG, "mkdirs path='%s' error='%d'", name.c_str(), error);
  
  cb(error);
}



}}}}
