/*
 * SWC-DB© Copyright since 2019 Alex Kashirin <kashirin.alex@gmail.com>
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */


#include "swcdb/db/client/Query/Update/BrokerCommitter.h"
#include "swcdb/db/Protocol/Bkr/req/Committer_CellsUpdate.h"


namespace SWC { namespace client { namespace Query { namespace Update {



#define SWC_BROKER_COMMIT_RSP_DEBUG(msg) \
  SWC_LOG_OUT(LOG_DEBUG, \
    print(SWC_LOG_OSTREAM << msg << ' '); \
    rsp.print(SWC_LOG_OSTREAM << ' '); \
    SWC_LOG_OSTREAM << " buff-sz=" << cells_buff.fill(); \
  );



void BrokerCommitter::print(std::ostream& out) {
  out << "BrokerCommitter(cid=" << colp->get_cid()
      << " completion=" << hdlr->completion.count()
      << ')';
}

void BrokerCommitter::commit() {
  hdlr->completion.increment();
  if(!hdlr->valid())
    return hdlr->response();

  workload.increment();
  bool more = true;
  DynamicBuffer cells_buff;

  while(more && hdlr->valid() &&
        colp->get_buff(hdlr->buff_sz, more, cells_buff)) {
    workload.increment();
    Comm::Protocol::Bkr::Req::Committer_CellsUpdate::request(
      shared_from_this(), std::move(cells_buff));
  }

  if(workload.is_last())
    hdlr->response();
}

void BrokerCommitter::committed(
                ReqBase::Ptr req,
                const Comm::Protocol::Bkr::Params::CellsUpdateRsp& rsp,
                const DynamicBuffer& cells_buff) {
  switch(rsp.err) {
    case Error::OK: {
      SWC_BROKER_COMMIT_RSP_DEBUG("bkr_commit");
      if(workload.is_last())
        hdlr->response();
      return;
    }

    case Error::COMM_NOT_CONNECTED:
    case Error::REQUEST_TIMEOUT: {
      if(hdlr->valid()) {
        SWC_BROKER_COMMIT_RSP_DEBUG("bkr_commit RETRYING");
        return req->request_again();
      }
      [[fallthrough]];
    }

    default: {
      hdlr->add_resend_count(colp->add(cells_buff));
      if(workload.is_last()) {
        if(hdlr->valid()) {
          SWC_BROKER_COMMIT_RSP_DEBUG("bkr_commit RETRYING");
          commit();
        }
        hdlr->response();
      }
      return;
    }
  }
}



}}}}
