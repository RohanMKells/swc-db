
/*
 * Copyright Since 2019 SWC-DB© [author: Kashirin Alex kashirin.alex@gmail.com]
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */

#ifndef swc_db_protocol_rgr_params_RangeIsLoaded_h
#define swc_db_protocol_rgr_params_RangeIsLoaded_h

#include "swcdb/db/Protocol/Common/params/ColRangeId.h"

namespace SWC { namespace Protocol { namespace Rgr { namespace Params {

class RangeIsLoaded : public Common::Params::ColRangeId {
  public:

  RangeIsLoaded() {}
  RangeIsLoaded(cid_t cid, rid_t rid) 
                : Common::Params::ColRangeId(cid, rid){}           
  virtual ~RangeIsLoaded() {}

};
  

}}}}

#endif // swc_db_protocol_rgr_params_RangeIsLoaded_h
