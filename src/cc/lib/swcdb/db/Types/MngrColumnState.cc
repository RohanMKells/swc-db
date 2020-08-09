
/*
 * Copyright Since 2019 SWC-DB© [author: Kashirin Alex kashirin.alex@gmail.com]
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */


#include "swcdb/db/Types/MngrColumnState.h"


namespace SWC { namespace Types { 


std::string to_string(MngrColumn::State state) {
  switch(state) {

    case MngrColumn::State::NOTSET:
      return std::string("NOTSET");

    case MngrColumn::State::OK:
      return std::string("OK");

    case MngrColumn::State::LOADING:
      return std::string("LOADING");

    case MngrColumn::State::DELETED:
      return std::string("DELETED");
      
    default:
      return std::string("uknown");
  }
}


}}
