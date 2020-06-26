/*
 * Copyright Since 2019 SWC-DB© [author: Kashirin Alex kashirin.alex@gmail.com]
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */


#include <sys/sysinfo.h>
#include <fstream>
#include "swcdb/core/sys/Resources.h"

#if defined TCMALLOC_MINIMAL || defined TCMALLOC
#include <gperftools/malloc_extension.h>
#endif

namespace SWC { 

Resources::Resources() : release(0) {
#if defined TCMALLOC_MINIMAL || defined TCMALLOC
  release_rate_default = MallocExtension::instance()->GetMemoryReleaseRate();
  if(release_rate_default < 0)
    release_rate_default = 0;
#endif
}

Resources::~Resources() {
  if(m_timer)
    delete m_timer;
}

void Resources::init(asio::io_context* io, 
                     Property::V_GINT32::Ptr ram_percent, 
                     Property::V_GINT32::Ptr ram_release_rate, 
                     const std::function<size_t(size_t)>& release_call) {
  if(m_timer == nullptr)
    m_timer = new asio::high_resolution_timer(*io);
    
  cfg_ram_percent = ram_percent;
  cfg_ram_release_rate = ram_release_rate;
  if(release_call)
    release = release_call;

  checker();
}

size_t Resources::need_ram() const {
  return ram.used > ram.allowed ? ram.used - ram.allowed : 0;
}

size_t Resources::avail_ram() const {
  return ram.allowed > ram.used  ? ram.allowed - ram.used : 0;
}

bool Resources::need_ram(uint32_t sz) const {
  return ram.free < sz * 2 || ram.used + sz > ram.allowed;
}

void Resources::stop() {
  m_timer->cancel();
}

std::string Resources::to_string() const {
  std::string s("Resources(");
  s.append("Mem-MB-");
  s.append(ram.to_string(1048576));
  s.append(")");
  return s;
}

void Resources::checker() {
  refresh_stats();

  if(size_t bytes = need_ram()) {
    if(release) {
      SWC_LOGF(LOG_DEBUG, "Resources release=%lld", bytes);
      size_t released_bytes = release(bytes);
      SWC_LOGF(LOG_DEBUG, "Resources released=%lld", released_bytes);
      if(released_bytes >= bytes)
        return schedule();
    }

#if defined TCMALLOC_MINIMAL || defined TCMALLOC
    if(!avail_ram()) {
      auto inst = MallocExtension::instance();
      inst->SetMemoryReleaseRate(cfg_ram_release_rate->get());
      inst->ReleaseFreeMemory();
      inst->SetMemoryReleaseRate(release_rate_default);
    }
#endif

  }
  schedule();
}

void Resources::refresh_stats() {
  if(++next_major_chk == 0) {
    page_size = sysconf(_SC_PAGE_SIZE);
    
    ram.total   = page_size * sysconf(_SC_PHYS_PAGES); 
    ram.free    = page_size * sysconf(_SC_AVPHYS_PAGES);
    ram.allowed = (ram.total/100) * cfg_ram_percent->get();
    ram.chk_ms  = ram.allowed / 3000; //~= ram-buff   
    if(ram.chk_ms > MAX_RAM_CHK_INTVAL_MS)
      ram.chk_ms = MAX_RAM_CHK_INTVAL_MS;
  }

  size_t sz = 0, rss = 0;
  std::ifstream buffer("/proc/self/statm");
  buffer >> sz >> rss;
  buffer.close();
  rss *= page_size;
  ram.used = ram.used > ram.allowed || ram.used > rss 
              ? (ram.used*4+rss)/5 
              : rss;
}

void Resources::schedule() {
  m_timer->expires_from_now(std::chrono::milliseconds(ram.chk_ms));
  m_timer->async_wait(
    [this](const asio::error_code ec) {
      if(ec != asio::error::operation_aborted) {
        checker();
      }
  }); 
}

std::string Resources::Component::to_string(uint32_t base) const {
  std::string s("Res(");
  s.append("total=");
  s.append(std::to_string(total/base));
  s.append(" free=");
  s.append(std::to_string(free/base));
  s.append(" used=");
  s.append(std::to_string(used/base));
  s.append(" allowed=");
  s.append(std::to_string(allowed/base));      
  s.append(")");
  return s;
}


namespace Env {

SWC::Resources Resources;

}


}
