/*
 * Copyright (C) 2019 SWC-DB (author: Kashirin Alex (kashirin.alex@gmail.com))
 */

#ifndef swc_lib_ranger_callbacks_RangeLocateScan_h
#define swc_lib_ranger_callbacks_RangeLocateScan_h

#include "swcdb/lib/core/comm/ResponseCallback.h"

namespace SWC {
namespace server {
namespace Rgr {
namespace Callback {


class RangeLocateScan : public ResponseCallback {
  public:

  RangeLocateScan(ConnHandlerPtr conn, EventPtr ev, Range::Ptr range)
                  : ResponseCallback(conn, ev), range(range) {
  }

  virtual ~RangeLocateScan() { }

  void response(int &err) override {

    if(err == Error::OK && Env::RgrData::is_shuttingdown()) 
      err = Error::SERVER_SHUTTING_DOWN;

    Protocol::Rgr::Params::RangeLocateRsp params(err);
    if(err == Error::OK) {
      if(req->cells->size() > 0) {

        DB::Cells::Cell cell;
        req->cells->get(0, cell);
        std::string id_name(cell.key.get_string(0));
        params.cid = (int64_t)strtoll(id_name.c_str(), NULL, 0);
      
        id_name = std::string((char *)cell.value, cell.vlen);
        params.rid = (int64_t)strtoll(id_name.c_str(), NULL, 0);

        params.key_start.set(cell.key, Condition::GE);
        if(req->cells->size() > 1) {
          req->cells->get(1, cell);
          params.key_next.set(cell.key, Condition::GE);
        }
      } else  {
        // range->cid == 1 || 2
        bool widen = false;
        if(req->spec->key_start.count > 1) {
          req->spec->key_start.remove(req->spec->key_start.count-1, true);
          widen = true;
        }
        if(req->spec->key_finish.count > 1) {
          req->spec->key_finish.remove(req->spec->key_finish.count-1, true);
          widen = true;
        }
        if(widen) {
          range->scan(req);
          return;
        } else {
          err = Error::RANGE_NOT_FOUND;
        }
      /* a miss for closest to under last key fraction 
      // opt, to add value with key_end comp to LE else next
      1 2 3 4 5 6
      1 2 3 4 5 6 a
      1 2 3 4 5 6 ab
      1 2 3 4 5 6 acb
      1 2 3 4 5 6 abc1           N  v(1 2 3 4 5 6 acb1)
      1 2 3 4 5 6 abc1 1         N  v(1 2 3 4 5 6 acb1 1)
      1 2 3 4 5 6 abc1 1  1 1    N
      1 2 3 4 5 6 abc1 2         N  v(1 2 3 4 5 6 acb1 7)
      1 2 3 4 5 6 abc1 8 a a a a ??? (next new key_begin)
      1 2 3 4 5 6 abc1 9  1 1    Y !!! v(1 2 3 4 5 6 acb1 98)
      1 2 3 4 5 6 abc1 99 1 1  
      1 2 3 4 5 6 acb2

      1 2 3 4 5 6 abc1 8 a a a a ?(which range)
      
      begin(widen) 1 2 3 4 5 6 abc1 + end(value)1 2 3 4 5 6 abc1 >=8
      */
      }
    }

    std::cout << "RangeLocateScan, rsp " << req->to_string() << "\n";

    try {
      CommHeader header;
      header.initialize_from_request_header(m_ev->header);
      CommBufPtr cbp = std::make_shared<CommBuf>(
        header, params.encoded_length());
      params.encode(cbp->get_data_ptr_address());

      m_conn->send_response(cbp);
    }
    catch (Exception &e) {
      HT_ERROR_OUT << e << HT_END;
    }
    
  }


  DB::Cells::ReqScan::Ptr req;
  Range::Ptr              range;

};
typedef std::shared_ptr<RangeLocateScan> RangeLocateScanPtr;


}
}}}
#endif // swc_lib_ranger_callbacks_RangeLocateScan_h
