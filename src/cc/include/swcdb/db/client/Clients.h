/*
 * Copyright Since 2019 SWC-DB© [author: Kashirin Alex kashirin.alex@gmail.com]
 */

#ifndef swc_db_client_Clients_h
#define swc_db_client_Clients_h

#include <memory>

#include "swcdb/core/comm/ClientConnQueues.h"
#include "swcdb/db/client/Settings.h"
#include "swcdb/db/client/AppContext.h"
#include "swcdb/db/client/Schemas.h"
#include "swcdb/db/client/mngr/Groups.h"
#include "swcdb/db/client/rgr/Rangers.h"

namespace SWC { namespace client {


IOCtxPtr default_io();


class Clients final {

  const AppContext::Ptr   m_app_ctx;

  public:

  typedef std::shared_ptr<Clients> Ptr;

  Clients(IOCtxPtr ioctx, const AppContext::Ptr& app_ctx);

  ~Clients();
  
  const Mngr::Groups::Ptr mngrs_groups;
  ConnQueuesPtr           mngr;
  ConnQueuesPtr           rgr;
  Schemas::Ptr            schemas;
  Rangers                 rangers;
};

} // namespace client 


namespace Env {
class Clients final {
  public:

  static void init(const client::Clients::Ptr& clients);

  static client::Clients::Ptr get();

  static const Clients& ref();

  const Property::V_GINT32::Ptr      cfg_send_buff_sz;
  const Property::V_GUINT8::Ptr      cfg_send_ahead;
  const Property::V_GINT32::Ptr      cfg_send_timeout;
  const Property::V_GINT32::Ptr      cfg_send_timeout_ratio;

  const Property::V_GINT32::Ptr      cfg_recv_buff_sz;
  const Property::V_GUINT8::Ptr      cfg_recv_ahead;
  const Property::V_GINT32::Ptr      cfg_recv_timeout;

  Clients(const client::Clients::Ptr& clients);

  ~Clients();

  private:
  client::Clients::Ptr                    m_clients = nullptr;
  inline static std::shared_ptr<Clients>  m_env = nullptr;
};
}

}


#ifdef SWC_IMPL_SOURCE
#include "swcdb/db/client/Clients.cc"
#include "swcdb/db/client/Schemas.cc"
#endif 


#endif // swc_db_client_Clients_h