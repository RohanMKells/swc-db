/*
 * SWC-DB© Copyright since 2019 Alex Kashirin <kashirin.alex@gmail.com>
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */


#include "swcdb/db/client/Clients.h"

namespace SWC { namespace client {

IOCtxPtr& default_io() {
  if(!Env::IoCtx::ok())
    Env::IoCtx::init(8);
  return Env::IoCtx::io()->shared();
}

Clients::Clients(IOCtxPtr ioctx, const AppContext::Ptr& app_ctx)
    : m_app_ctx(app_ctx),

      mngrs_groups(std::make_shared<Mngr::Groups>()->init()),

      mngr(std::make_shared<ConnQueues>(
        std::make_shared<Serialized>(
          "MANAGER", ioctx ? ioctx: ioctx = default_io(), m_app_ctx),
        Env::Config::settings()->get<Config::Property::V_GINT32>(
          "swc.client.Mngr.connection.timeout"),
        Env::Config::settings()->get<Config::Property::V_GINT32>(
          "swc.client.Mngr.connection.probes"),
        Env::Config::settings()->get<Config::Property::V_GINT32>(
          "swc.client.Mngr.connection.keepalive"),
        Env::Config::settings()->get<Config::Property::V_GINT32>(
          "swc.client.request.again.delay")
      )),

      rgr(std::make_shared<ConnQueues>(
        std::make_shared<Serialized>("RANGER", ioctx, m_app_ctx),
        Env::Config::settings()->get<Config::Property::V_GINT32>(
          "swc.client.Rgr.connection.timeout"),
        Env::Config::settings()->get<Config::Property::V_GINT32>(
          "swc.client.Rgr.connection.probes"),
        Env::Config::settings()->get<Config::Property::V_GINT32>(
          "swc.client.Rgr.connection.keepalive"),
        Env::Config::settings()->get<Config::Property::V_GINT32>(
          "swc.client.request.again.delay")
      )),

      schemas(std::make_shared<Schemas>(
        Env::Config::settings()->get<Config::Property::V_GINT32>(
          "swc.client.schema.expiry"))),

      rangers(Env::Config::settings()->get<Config::Property::V_GINT32>(
        "swc.client.Rgr.range.res.expiry")) {
}

Clients::~Clients() { }

} // namespace client 


namespace Env {

void Clients::init(const client::Clients::Ptr& clients) {
  m_env = std::make_shared<Clients>(clients);
}

client::Clients::Ptr Clients::get() {
  SWC_ASSERT(m_env != nullptr);
  return m_env->m_clients;
}

const Clients& Clients::ref() {
  return *m_env.get();
}

Clients::Clients(const client::Clients::Ptr& clients) 
          : cfg_send_buff_sz(
              Env::Config::settings()->get<SWC::Config::Property::V_GINT32>(
                "swc.client.send.buffer")),
            cfg_send_ahead(
              Env::Config::settings()->get<SWC::Config::Property::V_GUINT8>(
                "swc.client.send.ahead")),
            cfg_send_timeout(
              Env::Config::settings()->get<SWC::Config::Property::V_GINT32>(
                "swc.client.send.timeout")),
            cfg_send_timeout_ratio(
              Env::Config::settings()->get<SWC::Config::Property::V_GINT32>(
                "swc.client.send.timeout.bytes.ratio")),

            cfg_recv_buff_sz(
              Env::Config::settings()->get<SWC::Config::Property::V_GINT32>(
                "swc.client.recv.buffer")),
            cfg_recv_ahead(
              Env::Config::settings()->get<SWC::Config::Property::V_GUINT8>(
                "swc.client.recv.ahead")),
            cfg_recv_timeout(
              Env::Config::settings()->get<SWC::Config::Property::V_GINT32>(
                "swc.client.recv.timeout")),

            m_clients(clients) {
}

Clients::~Clients() { }

} 

} //namespace SWC

