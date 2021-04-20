/*
 * SWC-DB© Copyright since 2019 Alex Kashirin <kashirin.alex@gmail.com>
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */

#ifndef swcdb_db_protocol_rgr_req_RangeLocate_h
#define swcdb_db_protocol_rgr_req_RangeLocate_h


#include "swcdb/core/comm/ClientConnQueue.h"
#include "swcdb/db/Protocol/Rgr/params/RangeLocate.h"


namespace SWC { namespace Comm { namespace Protocol {
namespace Rgr { namespace Req {


class RangeLocate: public client::ConnQueue::ReqBase {
  public:

  typedef std::function<void(const client::ConnQueue::ReqBase::Ptr&,
                             const Params::RangeLocateRsp&)> Cb_t;

  static void request(const Params::RangeLocateReq& params,
                      const EndPoints& endpoints,
                      Cb_t&& cb,
                      const uint32_t timeout = 10000);

  RangeLocate(const Params::RangeLocateReq& params,
              const EndPoints& endpoints,
              Cb_t&& cb,
              const uint32_t timeout);

  virtual ~RangeLocate() { }

  void handle_no_conn() override;

  bool run() override;

  void handle(ConnHandlerPtr conn, const Event::Ptr& ev) override;

  const EndPoints  endpoints;
  const Cb_t       cb;

};


}}}}}


#ifdef SWC_IMPL_SOURCE
#include "swcdb/db/Protocol/Rgr/req/RangeLocate.cc"
#endif

#endif // swcdb_db_protocol_rgr_req_RangeLocate_h
