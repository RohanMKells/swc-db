
/*
 * Copyright Since 2019 SWC-DB© [author: Kashirin Alex kashirin.alex@gmail.com]
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */

#ifndef swc_db_protocol_req_RgrGet_h
#define swc_db_protocol_req_RgrGet_h


#include "swcdb/core/comm/ClientConnQueue.h"
#include "swcdb/db/Protocol/Mngr/params/RgrGet.h"


namespace SWC { namespace Protocol { namespace Mngr { namespace Req {

  
class RgrGet: public client::ConnQueue::ReqBase {
  public:
  
  typedef std::function<void(const client::ConnQueue::ReqBase::Ptr&, 
                             const Params::RgrGetRsp&)> Cb_t;
 
  static void request(cid_t cid, rid_t rid, bool next_range,
                      const Cb_t& cb, const uint32_t timeout = 10000);

  static void request(const Params::RgrGetReq& params,
                      const Cb_t& cb, const uint32_t timeout = 10000);

  static Ptr make(const Params::RgrGetReq& params,
                  const Cb_t& cb, const uint32_t timeout = 10000);

  RgrGet(const Params::RgrGetReq& params, const Cb_t& cb, 
            const uint32_t timeout);

  virtual ~RgrGet();

  void handle_no_conn() override;

  bool run(uint32_t timeout=0) override;

  void handle(ConnHandlerPtr conn, const Event::Ptr& ev) override;

  private:
  
  void clear_endpoints();

  const Cb_t  cb;
  EndPoints   endpoints;
  cid_t       cid;
};


}}}}


#ifdef SWC_IMPL_SOURCE
#include "swcdb/db/Protocol/Mngr/req/RgrGet.cc"
#endif 

#endif // swc_db_protocol_req_RgrGet_h
