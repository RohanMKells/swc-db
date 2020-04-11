/*
 * Copyright Since 2019 SWC-DB© [author: Kashirin Alex kashirin.alex@gmail.com]
 */


#ifndef swc_ranger_Protocol_handlers_RangeQuerySelect_h
#define swc_ranger_Protocol_handlers_RangeQuerySelect_h

#include "swcdb/db/Protocol/Rgr/params/RangeQuerySelect.h"
#include "swcdb/ranger/callbacks/RangeQuerySelect.h"


namespace SWC { namespace Protocol { namespace Rgr { namespace Handler {


void range_query_select(ConnHandlerPtr conn, Event::Ptr ev) {
  int err = Error::OK;
  Params::RangeQuerySelectReq params;
  Ranger::RangePtr range;

  try {
    const uint8_t *ptr = ev->data.base;
    size_t remain = ev->data.size;
    params.decode(&ptr, &remain);

    range = RangerEnv::columns()->get_range(err, params.cid, params.rid);
 
    if(!err && (range == nullptr || !range->is_loaded()))
      err = Error::RS_NOT_LOADED_RANGE;

  } catch (Exception &e) {
    SWC_LOG_OUT(LOG_ERROR) << e << SWC_LOG_OUT_END;
    err = e.code();
  }

  try{
      
    if(err) {
      Protocol::Rgr::Params::RangeQuerySelectRsp rsp_params(err);
      auto cbp = CommBuf::make(rsp_params);
      cbp->header.initialize_from_request_header(ev->header);
      conn->send_response(cbp);
      return;
    }
    
    params.interval.apply_possible_range(
      params.interval.range_begin, params.interval.range_end);

    range->scan(
      std::make_shared<Ranger::Callback::RangeQuerySelect>(
        conn, ev, params.interval, 
        DB::Cells::ReqScan::Config(
          range->cfg->column_type(),
          params.interval.flags.max_versions 
            ? params.interval.flags.max_versions 
            : range->cfg->cell_versions(),
          range->cfg->cell_ttl(), 
          params.limit_buffer_sz
        ),
        range
      )
    );
  } catch (Exception &e) {
    SWC_LOG_OUT(LOG_ERROR) << e << SWC_LOG_OUT_END;
  }
  
}
  

}}}}

#endif // swc_ranger_Protocol_handlers_RangeQuerySelect_h