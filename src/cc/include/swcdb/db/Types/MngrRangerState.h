
/*
 * Copyright Since 2019 SWC-DB© [author: Kashirin Alex kashirin.alex@gmail.com]
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */

#ifndef swc_db_types_MngrRangerState_h
#define swc_db_types_MngrRangerState_h

#include <string>

namespace SWC { namespace Types {  


namespace MngrRanger {

  enum State {
    NONE            = 0,
    AWAIT           = 1,
    ACK             = 2,
    REMOVED         = 3,
    MARKED_OFFLINE  = 4
  };

}


std::string to_string(MngrRanger::State state);


}}

#ifdef SWC_IMPL_SOURCE
#include "swcdb/db/Types/MngrRangerState.cc"
#endif 

#endif // swc_db_types_MngrRangerState_h
