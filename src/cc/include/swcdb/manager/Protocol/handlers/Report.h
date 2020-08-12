/*
 * Copyright Since 2019 SWC-DB© [author: Kashirin Alex kashirin.alex@gmail.com]
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */


#ifndef swc_manager_Protocol_handlers_Report_h
#define swc_manager_Protocol_handlers_Report_h

#include "swcdb/db/Protocol/Mngr/params/Report.h"


namespace SWC { namespace Protocol { namespace Mngr { namespace Handler {


void report(const ConnHandlerPtr& conn, const Event::Ptr& ev) {
  
  int err = Error::OK;
  CommBuf::Ptr cbp;

  try {
    
    const uint8_t *ptr = ev->data.base;
    size_t remain = ev->data.size;

    auto func((Params::Report::Function)Serialization::decode_i8(&ptr, &remain));
    
    switch(func) {

      case Params::Report::Function::CLUSTER_STATUS: {
        
        if(Env::Mngr::mngd_columns()->is_schemas_mngr(err) && err)
          goto function_send_response;

        if(Env::Mngr::mngd_columns()->has_cid_pending_load()) {
          err = Error::MNGR_NOT_INITIALIZED;
          goto function_send_response;
        }

        if(Env::Mngr::role()->is_active_role(Types::MngrRole::RANGERS) &&
           Env::Mngr::rangers()->empty()) {
          err = Error::MNGR_NOT_INITIALIZED;
          goto function_send_response;
        }

        if(Env::Mngr::mngd_columns()->has_active()) {
          Env::Mngr::columns()->state(err);
        }
        
        function_send_response:
          cbp = CommBuf::make(4);
          cbp->append_i32(err);
          goto send_response;
      }

      case Params::Report::Function::MANAGERS_STATUS: {
        auto& role = *Env::Mngr::role();

        Manager::MngrsStatus mngrs;
        role.get_states(mngrs);
        
        Params::Report::RspManagersStatus rsp_params;
        rsp_params.managers.resize(mngrs.size());
        size_t i = 0;
        for(auto& mngr : mngrs) {
          auto& m = rsp_params.managers[i];
          m.priority = mngr->priority;
          m.state = mngr->state;
          m.role = mngr->role;
          m.cid_begin = mngr->cid_begin;
          m.cid_end = mngr->cid_end;
          m.failures = mngr->failures;
          m.endpoints = mngr->endpoints;
          ++i;
        }
        rsp_params.inchain = role.get_inchain_endpoint();
          
        cbp = CommBuf::make(rsp_params, 4);
        cbp->append_i32(err);
        goto send_response;
      }

      case Params::Report::Function::RANGERS_STATUS: {
        auto& mngr_rangers = *Env::Mngr::rangers();

        Manager::RangerList rangers;
        mngr_rangers.rgr_list(0, rangers);
        
        Params::Report::RspRangersStatus rsp_params;
        rsp_params.rangers.resize(rangers.size());
        size_t i = 0;
        for(auto& rgr : rangers) {
          auto& r = rsp_params.rangers[i];
          r.state = rgr->state;
          r.rgr_id = rgr->rgrid;
          r.failures = rgr->failures;
          r.interm_ranges = rgr->interm_ranges;
          r.load_scale = rgr->load_scale;
          mngr_rangers.rgr_get(rgr, r.endpoints);
          ++i;
        }
        cbp = CommBuf::make(rsp_params, 4);
        cbp->append_i32(err);
        goto send_response;
      }

      case Params::Report::Function::COLUMN_STATUS: {
        Params::Report::ReqColumnStatus params;
        params.decode(&ptr, &remain);
        
        Params::Report::RspColumnStatus rsp_params;
        auto col = Env::Mngr::mngd_columns()->get_column(err, params.cid);
        if(err == Error::COLUMN_NOT_READY)
          err = Error::OK;
        else if(err)
          goto send_error;

        std::vector<Manager::Range::Ptr> ranges;
        col->get_ranges(ranges);
        rsp_params.ranges.resize(ranges.size());
        size_t i = 0; 
        for(auto& r : ranges) {
          auto& set_r = rsp_params.ranges[i];
          set_r.state = r->state();
          set_r.rid = r->rid;
          set_r.rgr_id = r->get_rgr_id();
          ++i;
        }
        rsp_params.state = col->state();
        cbp = CommBuf::make(rsp_params, 4);
        cbp->append_i32(err);
        goto send_response;
      }

      default:
        err = Error::NOT_IMPLEMENTED;
        break;
    }
    
  } catch (Exception &e) {
    SWC_LOG_OUT(LOG_ERROR) << e << SWC_LOG_OUT_END;
    err = e.code();
  }

  
  send_error:
    cbp = CommBuf::make(4);
    cbp->append_i32(err);


  send_response:
    try {
      cbp->header.initialize_from_request_header(ev->header);
      conn->send_response(cbp);
    } catch (Exception &e) {
      SWC_LOG_OUT(LOG_ERROR) << e << SWC_LOG_OUT_END;
    }

}



}}}}

#endif // swc_manager_Protocol_handlers_:Report_h
