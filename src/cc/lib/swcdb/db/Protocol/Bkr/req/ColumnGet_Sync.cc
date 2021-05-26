/*
 * SWC-DB© Copyright since 2019 Alex Kashirin <kashirin.alex@gmail.com>
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */


#include "swcdb/db/Protocol/Bkr/req/ColumnGet_Sync.h"
#include "swcdb/db/client/Clients.h"
#include "swcdb/db/Protocol/Commands.h"


namespace SWC { namespace Comm { namespace Protocol {
namespace Bkr { namespace Req {


SWC_SHOULD_INLINE
void ColumnGet_Sync::schema(const SWC::client::Clients::Ptr& clients,
                            int& err, const std::string& name,
                            DB::Schema::Ptr& _schema,
                            const uint32_t timeout) {
  request(
    clients,
    Mngr::Params::ColumnGetReq(
      Mngr::Params::ColumnGetReq::Flag::SCHEMA_BY_NAME, name),
    err, _schema, timeout
  );
}

SWC_SHOULD_INLINE
void ColumnGet_Sync::schema(const SWC::client::Clients::Ptr& clients,
                            int& err, cid_t cid,
                            DB::Schema::Ptr& _schema,
                            const uint32_t timeout) {
  request(
    clients,
    Mngr::Params::ColumnGetReq(
      Mngr::Params::ColumnGetReq::Flag::SCHEMA_BY_ID, cid),
    err, _schema, timeout
  );
}

SWC_SHOULD_INLINE
void ColumnGet_Sync::request(const SWC::client::Clients::Ptr& clients,
                             const Mngr::Params::ColumnGetReq& params,
                             int& err, DB::Schema::Ptr& _schema,
                             const uint32_t timeout) {
  auto req = std::make_shared<ColumnGet_Sync>(
    clients, params, err, _schema, timeout);
  auto res = req->await.get_future();
  req->run();
  res.get();
}


ColumnGet_Sync::ColumnGet_Sync(
                const SWC::client::Clients::Ptr& clients,
                const Mngr::Params::ColumnGetReq& params,
                int& err, DB::Schema::Ptr& _schema,
                const uint32_t timeout)
                : client::ConnQueue::ReqBase(
                    false,
                    Buffers::make(params, 0, COLUMN_GET, timeout)
                  ),
                  clients(clients), err(err), _schema(_schema) {
}

void ColumnGet_Sync::handle_no_conn() {
  if(clients->stopping()) {
    err = Error::CLIENT_STOPPING;
    await.set_value();
  } else if(_bkr_idx.turn_around(clients->brokers)) {
    request_again();
  } else {
    run();
  }
}

bool ColumnGet_Sync::run() {
  EndPoints endpoints;
  while(!clients->stopping() &&
        (endpoints = clients->brokers.get_endpoints(_bkr_idx)).empty()) {
    SWC_LOG(LOG_ERROR,
      "Broker hosts cfg 'swc.bkr.host' is empty, waiting!");
    std::this_thread::sleep_for(std::chrono::seconds(3));
  }
  if(endpoints.empty()) {
    handle_no_conn();
    return false;
  }
  clients->get_bkr_queue(endpoints)->put(req());
  return true;
}

void ColumnGet_Sync::handle(ConnHandlerPtr, const Event::Ptr& ev) {
  if(ev->type == Event::Type::DISCONNECT)
    return handle_no_conn();

  err = ev->response_code();
  if(!err) {
    try {
      const uint8_t *ptr = ev->data.base + 4;
      size_t remain = ev->data.size - 4;
      Mngr::Params::ColumnGetRsp rsp;
      rsp.decode(&ptr, &remain);
      _schema = std::move(rsp.schema);

    } catch(...) {
      const Error::Exception& e = SWC_CURRENT_EXCEPTION("");
      SWC_LOG_OUT(LOG_ERROR, SWC_LOG_OSTREAM << e; );
      err = e.code();
    }

  } else if(err == Error::REQUEST_TIMEOUT) {
    SWC_LOG_OUT(LOG_INFO, Error::print(SWC_LOG_OSTREAM, err); );
    request_again();
    return;
  }

  await.set_value();
}



}}}}}
