/*
 * SWC-DB© Copyright since 2019 Alex Kashirin <kashirin.alex@gmail.com>
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */


#ifndef swcdb_core_comm_Event_h
#define swcdb_core_comm_Event_h


#include "swcdb/core/Time.h"
#include "swcdb/core/Buffer.h"
#include "swcdb/core/comm/Header.h"


namespace SWC { namespace Comm {

class Event final {

  protected:

  SWC_CAN_INLINE
  explicit Event(int error) noexcept : expiry_ms(0), error(error) { }

  public:

  typedef std::shared_ptr<Event> Ptr;

  SWC_CAN_INLINE
  static Ptr make(int error) {
    return Ptr(new Event(error));
  }

  //~Event() { }

  SWC_CAN_INLINE
  void received() noexcept {
    if(header.timeout_ms)
      expiry_ms = Time::now_ms() + header.timeout_ms - 1;
  }

  void decode_buffers();

  bool expired(int64_t within=0) const noexcept;

  int32_t response_code() const noexcept;

  void print(std::ostream& out) const;

  int64_t             expiry_ms;
  StaticBuffer        data;     //!< Primary data buffer
  StaticBuffer        data_ext; //!< Extended buffer
  Header              header;
  int                 error;

};

}} // namespace SWC::Comm


#ifdef SWC_IMPL_SOURCE
#include "swcdb/core/comm/Event.cc"
#endif

#endif // swcdb_core_comm_Event_h
