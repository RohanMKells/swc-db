/* 
 * Copyright (C) 2019 SWC-DB (author: Kashirin Alex (kashirin.alex@gmail.com))
 */


#ifndef swc_core_comm_Event_h
#define swc_core_comm_Event_h

#include "CommHeader.h"

#include "swcdb/lib/core/Clock.h"
#include "swcdb/lib/core/String.h"
#include "swcdb/lib/core/Logger.h"

#include <iostream>
#include <memory>

namespace SWC {

  class Event {

  public:

    /** Enumeration for event types.
     */
    enum Type { 
      CONNECTION_ESTABLISHED, ///< Connection established event
      DISCONNECT,             ///< Connection disconnected event
      MESSAGE,                ///< Request/response message event
      ERROR,                  ///< %Error event
    };

    Event(Type type_, int error_) 
         : type(type_), error(error_), arrival_time(ClockT::now()) {
     }


    /** Destructor.  Deallocates message payload buffer and proxy name buffer
     */
    ~Event() {
      if (payload_aligned)
        free((void *)payload);
      else
        delete [] payload;
    }

    /** Loads header object from serialized message buffer.  This method
     * also sets the group_id member.
     *
     * @param buf Buffer containing serialized header
     * @param len Length of buffer
     */
    void load_message_header(const uint8_t *buf, size_t len) {
      header.decode(&buf, &len);
    }

    /** Deadline for request.
     * @return Absolute deadline
     */
    ClockT::time_point deadline() {
      HT_ASSERT(arrival_time.time_since_epoch().count() > 0);
      return arrival_time + std::chrono::milliseconds(header.timeout_ms);
    }

    Type type;
    int error {};
    CommHeader header;
    const uint8_t *payload {};
    size_t payload_len {};
    ClockT::time_point arrival_time {};

    /// Flag indicating if payload was allocated with posix_memalign
    bool payload_aligned {};

    /** Generates a one-line string representation of the event.  For example:
     * <pre>
     *   Event: type=MESSAGE id=2 gid=0 header_len=16 total_len=20 \
     *   from=127.0.0.1:15861 ...
     * </pre>
     */
    String to_str() const {
      std::string dstr = "Event: type=";
      switch(type){
        case CONNECTION_ESTABLISHED:
          dstr += "CONNECTION_ESTABLISHED";
          break;
        case DISCONNECT:
          dstr += "DISCONNECT";
          break;
        case MESSAGE:
          dstr += "MESSAGE" + header.to_string();
          break;
        case ERROR:
          dstr += "ERROR";
          break;
        default:
          dstr += "UKNOWN("+ std::to_string((int)type)+")";
          break;
      }
      
      if (error != Error::OK)
        dstr += (String)" \"" + Error::get_text(error) + "\"";

      if(payload_len > 0)
        dstr += (String)" payload=\"" 
             + std::string((const char*)payload, payload_len<256?payload_len:256) + "\"";

      return dstr;
    }

    /** Displays a one-line string representation of the event to stdout.
     * @see to_str
     */
    void display() { std::cerr << to_str() << std::endl; }
    
  };

  /// Smart pointer to Event
  typedef std::shared_ptr<Event> EventPtr;
  /** @}*/


} // namespace SWC

#endif // swc_core_comm_Event_h
