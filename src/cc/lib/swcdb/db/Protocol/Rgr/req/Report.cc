
/*
 * SWC-DB© Copyright since 2019 Alex Kashirin <kashirin.alex@gmail.com>
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */


#include "swcdb/db/client/Clients.h"
#include "swcdb/db/Protocol/Commands.h"
#include "swcdb/db/Protocol/Rgr/req/Report.h"


namespace SWC { namespace Protocol { namespace Rgr { namespace Req {



Report::Report(const Comm::EndPoints& endpoints, Params::Report::Function func, 
               const uint32_t timeout)
              : Comm::client::ConnQueue::ReqBase(false), 
                endpoints(endpoints) {
  cbp = Comm::Buffers::make(1);
  cbp->append_i8((uint8_t)func);
  cbp->header.set(REPORT, timeout);
}

Report::Report(const Comm::EndPoints& endpoints, Params::Report::Function func, 
               const Serializable& params, const uint32_t timeout) 
              : Comm::client::ConnQueue::ReqBase(false), 
                endpoints(endpoints) {
  cbp = Comm::Buffers::make(params, 1);
  cbp->append_i8((uint8_t)func);
  cbp->header.set(REPORT, timeout);
}

Report::~Report() { }

bool Report::run() {
  Env::Clients::get()->rgr->get(endpoints)->put(req());
  return true;
}



SWC_SHOULD_INLINE
void ReportRes::request(const Comm::EndPoints& endpoints, 
                        const ReportRes::Cb_t& cb,
                        const uint32_t timeout) {
  std::make_shared<ReportRes>(endpoints, cb, timeout)->run();
}

ReportRes::ReportRes(const Comm::EndPoints& endpoints, 
                     const Cb_t& cb, 
                     const uint32_t timeout)
                     : Report(
                        endpoints,
                        Params::Report::Function::RESOURCES,
                        timeout
                      ), cb(cb) {
}

ReportRes::~ReportRes() { }

void ReportRes::handle_no_conn() {
  cb(req(), Error::COMM_CONNECT_ERROR, Params::Report::RspRes());
}

void ReportRes::handle(Comm::ConnHandlerPtr, const Comm::Event::Ptr& ev) {
  if(ev->type == Comm::Event::Type::DISCONNECT)
    return handle_no_conn();

  Params::Report::RspRes rsp_params;
  int err = ev->error;
  if(!err) {
    try {
      const uint8_t *ptr = ev->data.base;
      size_t remain = ev->data.size;

      err = Serialization::decode_i32(&ptr, &remain);
      if(!err)
        rsp_params.decode(&ptr, &remain);

    } catch(...) {
      const Exception& e = SWC_CURRENT_EXCEPTION("");
      SWC_LOG_OUT(LOG_ERROR, SWC_LOG_OSTREAM << e; );
      err = e.code();
    }
  }

  cb(req(), err, rsp_params);
}



SWC_SHOULD_INLINE
void ReportCids::request(const Comm::EndPoints& endpoints, 
                         const ReportCids::Cb_t& cb,
                         const uint32_t timeout) {
  std::make_shared<ReportCids>(endpoints, cb, timeout)->run();
}

ReportCids::ReportCids(const Comm::EndPoints& endpoints, 
                       const Cb_t& cb, 
                       const uint32_t timeout)
                      : Report(
                          endpoints,
                          Params::Report::Function::CIDS,
                          timeout
                        ), cb(cb) {
}

ReportCids::~ReportCids() { }

void ReportCids::handle_no_conn() {
  cb(req(), Error::COMM_CONNECT_ERROR, Params::Report::RspCids());
}

void ReportCids::handle(Comm::ConnHandlerPtr, const Comm::Event::Ptr& ev) {
  if(ev->type == Comm::Event::Type::DISCONNECT)
    return handle_no_conn();
  
  Params::Report::RspCids rsp_params;
  int err = ev->error;
  if(!err) {
    try {
      const uint8_t *ptr = ev->data.base;
      size_t remain = ev->data.size;

      err = Serialization::decode_i32(&ptr, &remain);
      if(!err)
        rsp_params.decode(&ptr, &remain);

    } catch(...) {
      const Exception& e = SWC_CURRENT_EXCEPTION("");
      SWC_LOG_OUT(LOG_ERROR, SWC_LOG_OSTREAM << e; );
      err = e.code();
    }
  }

  cb(req(), err, rsp_params);
}



SWC_SHOULD_INLINE
void ReportColumnRids::request(const Comm::EndPoints& endpoints, cid_t cid, 
                            const ReportColumnRids::Cb_t& cb, 
                            const uint32_t timeout) {
  std::make_shared<ReportColumnRids>(endpoints, cid, cb, timeout)->run();
}

ReportColumnRids::ReportColumnRids(const Comm::EndPoints& endpoints, cid_t cid,
                                   const Cb_t& cb, const uint32_t timeout)
                                  : Report(
                                      endpoints,
                                      Params::Report::Function::COLUMN_RIDS,
                                      Params::Report::ReqColumn(cid),
                                      timeout
                                    ), cb(cb) {
}

ReportColumnRids::~ReportColumnRids() { }

void ReportColumnRids::handle_no_conn() {
  cb(req(), Error::COMM_CONNECT_ERROR, Params::Report::RspColumnRids());
}

void ReportColumnRids::handle(Comm::ConnHandlerPtr, const Comm::Event::Ptr& ev) {
  if(ev->type == Comm::Event::Type::DISCONNECT)
    return handle_no_conn();
  
  Params::Report::RspColumnRids rsp_params;
  int err = ev->error;
  if(!err) {
    try {
      const uint8_t *ptr = ev->data.base;
      size_t remain = ev->data.size;

      err = Serialization::decode_i32(&ptr, &remain);
      if(!err)
        rsp_params.decode(&ptr, &remain);

    } catch(...) {
      const Exception& e = SWC_CURRENT_EXCEPTION("");
      SWC_LOG_OUT(LOG_ERROR, SWC_LOG_OSTREAM << e; );
      err = e.code();
    }
  }

  cb(req(), err, rsp_params);
}



SWC_SHOULD_INLINE
void ReportColumnsRanges::request(const Comm::EndPoints& endpoints,
                                  const ReportColumnsRanges::Cb_t& cb, 
                                  const uint32_t timeout) {
  std::make_shared<ReportColumnsRanges>(endpoints, cb, timeout)->run();
}

SWC_SHOULD_INLINE
void ReportColumnsRanges::request(const Comm::EndPoints& endpoints, 
                                  cid_t cid, 
                                  const ReportColumnsRanges::Cb_t& cb, 
                                  const uint32_t timeout) {
  std::make_shared<ReportColumnsRanges>(endpoints, cid, cb, timeout)->run();
}

ReportColumnsRanges::ReportColumnsRanges(
            const Comm::EndPoints& endpoints,
            const Cb_t& cb, 
            const uint32_t timeout)
            : Report(
                endpoints,
                Params::Report::Function::COLUMNS_RANGES,
                timeout
              ), cb(cb) {
}

ReportColumnsRanges::ReportColumnsRanges(
          const Comm::EndPoints& endpoints, 
          cid_t cid, 
          const Cb_t& cb, 
          const uint32_t timeout)
          : Report(
              endpoints,
              Params::Report::Function::COLUMN_RANGES,
              Params::Report::ReqColumn(cid),
              timeout
            ), cb(cb) {
}

ReportColumnsRanges::~ReportColumnsRanges() { }

void ReportColumnsRanges::handle_no_conn() {
  cb(req(), Error::COMM_CONNECT_ERROR, Params::Report::RspColumnsRanges());
}

void ReportColumnsRanges::handle(Comm::ConnHandlerPtr, const Comm::Event::Ptr& ev) {
  if(ev->type == Comm::Event::Type::DISCONNECT)
    return handle_no_conn();
  
  Params::Report::RspColumnsRanges rsp_params;
  int err = ev->error;
  if(!err) {
    try {
      const uint8_t *ptr = ev->data.base;
      size_t remain = ev->data.size;

      err = Serialization::decode_i32(&ptr, &remain);
      if(!err)
        rsp_params.decode(&ptr, &remain);

    } catch(...) {
      const Exception& e = SWC_CURRENT_EXCEPTION("");
      SWC_LOG_OUT(LOG_ERROR, SWC_LOG_OSTREAM << e; );
      err = e.code();
    }
  }

  cb(req(), err, rsp_params);
}







}}}}
