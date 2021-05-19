/*
 * SWC-DB© Copyright since 2019 Alex Kashirin <kashirin.alex@gmail.com>
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */

#ifndef swcdb_db_client_brk_Brokers_h
#define swcdb_db_client_brk_Brokers_h


#include "swcdb/db/client/service/bkr/ContextBroker.h"
#include "swcdb/core/comm/ClientConnQueues.h"


namespace SWC { namespace client {



class Brokers {
  public:

  Brokers() noexcept : queues(nullptr), cfg_hosts(nullptr) { }

  Brokers(const Config::Settings& settings,
          Comm::IoContextPtr ioctx,
          const ContextBroker::Ptr& bkr_ctx);

  //~Brokers() { }

  Comm::EndPoints get_endpoints() const;

  const Comm::client::ConnQueuesPtr        queues;
  const Config::Property::V_GSTRINGS::Ptr  cfg_hosts;
};



}} // namespace SWC::client




#ifdef SWC_IMPL_SOURCE
#include "swcdb/db/client/service/bkr/Brokers.cc"
#endif


#endif // swcdb_db_client_brk_Brokers_h
