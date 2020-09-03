
/*
 * Copyright Since 2019 SWC-DB© [author: Kashirin Alex kashirin.alex@gmail.com]
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */


#include "swcdb/core/Logger.h"
#include "swcdb/core/comm/AppContext.h"
#include <iostream>

namespace SWC {

AppContext::AppContext() { }

AppContext::~AppContext(){}

void AppContext::handle(ConnHandlerPtr, const Event::Ptr& ev) {
  SWC_LOG_OUT(LOG_WARN, SWC_LOG_OSTREAM
    << "AppContext(handle is Virtual!)\n" << ev->to_str(); );
}

void AppContext::init(const EndPoints& endpoints) {
  m_endpoints = endpoints;
}
  
void AppContext::stop() {
  std::cerr << "AppContext(stop is Virtual)!\n";
}


}
