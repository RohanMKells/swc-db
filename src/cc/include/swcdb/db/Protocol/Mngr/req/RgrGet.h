/*
 * SWC-DB© Copyright since 2019 Alex Kashirin <kashirin.alex@gmail.com>
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */

#ifndef swcdb_db_protocol_req_RgrGet_h
#define swcdb_db_protocol_req_RgrGet_h


#include "swcdb/db/Protocol/Mngr/req/RgrGet_Base.h"


namespace SWC { namespace Comm { namespace Protocol {
namespace Mngr { namespace Req {


class RgrGet: public RgrGet_Base {
  public:

  typedef std::function<void(const client::ConnQueue::ReqBase::Ptr&,
                             const Params::RgrGetRsp&)> Cb_t;

  static void request(const SWC::client::Clients::Ptr& clients,
                      cid_t cid, rid_t rid, bool next_range,
                      Cb_t&& cb, const uint32_t timeout = 10000);

  static void request(const SWC::client::Clients::Ptr& clients,
                      const Params::RgrGetReq& params,
                      Cb_t&& cb, const uint32_t timeout = 10000);

  static Ptr make(const SWC::client::Clients::Ptr& clients,
                  const Params::RgrGetReq& params,
                  Cb_t&& cb, const uint32_t timeout = 10000);

  virtual ~RgrGet() { }

  protected:

  RgrGet(const SWC::client::Clients::Ptr& clients,
         const Params::RgrGetReq& params, Cb_t&& cb,
         const uint32_t timeout);

  virtual SWC::client::Clients::Ptr& get_clients() noexcept override {
    return clients;
  }

  virtual void callback(const Params::RgrGetRsp&) override;


  private:
  SWC::client::Clients::Ptr clients;
  const Cb_t                cb;
};


}}}}}


#ifdef SWC_IMPL_SOURCE
#include "swcdb/db/Protocol/Mngr/req/RgrGet.cc"
#endif

#endif // swcdb_db_protocol_req_RgrGet_h
