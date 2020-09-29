
/*
 * SWC-DB© Copyright since 2019 Alex Kashirin <kashirin.alex@gmail.com>
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */

#ifndef swc_db_protocol_mngr_req_ColumnGet_h
#define swc_db_protocol_mngr_req_ColumnGet_h


#include "swcdb/db/Protocol/Mngr/params/ColumnGet.h"
#include "swcdb/core/comm/ClientConnQueue.h"


namespace SWC { namespace Protocol { namespace Mngr { namespace Req {

  
class ColumnGet: public Comm::client::ConnQueue::ReqBase {
  public:
  
  using Flag = Params::ColumnGetReq::Flag;
  typedef std::function<void(const Comm::client::ConnQueue::ReqBase::Ptr&, 
                             int, const Params::ColumnGetRsp&)> Cb_t;


  static void schema(const std::string& name, const Cb_t& cb, 
                     const uint32_t timeout = 10000);
  
  static void schema(cid_t cid, const Cb_t& cb, 
                     const uint32_t timeout = 10000);

  static void cid(const std::string& name, const Cb_t& cb, 
                  const uint32_t timeout = 10000);

  static void request(Flag flag, const std::string& name, const Cb_t& cb,
                      const uint32_t timeout = 10000);

  static void request(Flag flag, cid_t cid, const Cb_t& cb, 
                      const uint32_t timeout = 10000);


  ColumnGet(const Params::ColumnGetReq& params, const Cb_t& cb, 
            const uint32_t timeout);

  virtual ~ColumnGet();

  void handle_no_conn() override;

  bool run() override;

  void handle(Comm::ConnHandlerPtr conn, const Comm::Event::Ptr& ev) override;

  private:
  
  void clear_endpoints();

  const Cb_t        cb;
  Comm::EndPoints   endpoints;
};



}}}}


#ifdef SWC_IMPL_SOURCE
#include "swcdb/db/Protocol/Mngr/req/ColumnGet.cc"
#endif 

#endif // swc_db_protocol_mngr_req_ColumnGet_h
