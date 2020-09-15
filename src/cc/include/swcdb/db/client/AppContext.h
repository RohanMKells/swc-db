/*
 * SWC-DB© Copyright since 2019 Alex Kashirin <kashirin.alex@gmail.com>
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */

#ifndef swc_db_client_AppContext_h
#define swc_db_client_AppContext_h

#include "swcdb/core/comm/ConnHandler.h"

namespace SWC { namespace client { 

class AppContext : public SWC::AppContext {
  public:

  AppContext();

  virtual ~AppContext();

  void handle(ConnHandlerPtr conn, const Event::Ptr& ev) override;
  
};

}}



#ifdef SWC_IMPL_SOURCE
#include "swcdb/db/client/AppContext.cc"
#endif 

#endif // swc_db_client_AppContext_h