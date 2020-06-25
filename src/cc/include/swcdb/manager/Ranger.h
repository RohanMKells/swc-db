
/*
 * Copyright Since 2019 SWC-DB© [author: Kashirin Alex kashirin.alex@gmail.com]
 */

#ifndef swc_manager_Ranger_h
#define swc_manager_Ranger_h

#include "swcdb/db/Protocol/Common/params/HostEndPoints.h"


namespace SWC { namespace Manager {


class Ranger : public Protocol::Common::Params::HostEndPoints {

  public:

  enum State {
    NONE,
    AWAIT,
    ACK,
    REMOVED
  };
  typedef std::shared_ptr<Ranger> Ptr;

  Ranger(): rgrid(0), state(State::NONE), 
            failures(0), total_ranges(0) {}
                       
  Ranger(rgrid_t rgrid, const EndPoints& endpoints)
        : rgrid(rgrid), state(State::NONE), 
          failures(0), total_ranges(0),
          Protocol::Common::Params::HostEndPoints(endpoints) {
  }

  virtual ~Ranger(){}

  std::string to_string(){
    std::string s("[rgrid=");
    s.append(std::to_string(rgrid));
    s.append(", state=");
    s.append(std::to_string(state));
    s.append(", failures=");
    s.append(std::to_string(failures));
    s.append(", total_ranges=");
    s.append(std::to_string(total_ranges));
    s.append(", ");
    s.append(Protocol::Common::Params::HostEndPoints::to_string());
    if(m_queue != nullptr) {
      s.append(", ");
      s.append(m_queue->to_string());
    }
    s.append("]");
    return s;
  }

  size_t internal_encoded_length() const {
    size_t len = 1
      + Serialization::encoded_length_vi64(rgrid)
      + Protocol::Common::Params::HostEndPoints::internal_encoded_length();
    return len;
  }

  void internal_encode(uint8_t** bufp) const {
    Serialization::encode_i8(bufp, (uint8_t)state);
    Serialization::encode_vi64(bufp, rgrid);
    Protocol::Common::Params::HostEndPoints::internal_encode(bufp);
  }

  void internal_decode(const uint8_t** bufp, size_t* remainp) {
    state = (State)Serialization::decode_i8(bufp, remainp);
    rgrid = Serialization::decode_vi64(bufp, remainp);
    Protocol::Common::Params::HostEndPoints::internal_decode(bufp, remainp);
  }

  void init_queue(){
    m_queue = Env::Clients::get()->rgr->get(endpoints);
  }

  void put(const client::ConnQueue::ReqBase::Ptr& req){
    m_queue->put(req);
  }

  void stop(){
    m_queue->stop();
  }

  void pending_id(const client::ConnQueue::ReqBase::Ptr& req){
    m_pending_id.push(req);
  }

  bool pending_id_pop(client::ConnQueue::ReqBase::Ptr& req){
    if(m_pending_id.empty())
      return false;
    req = m_pending_id.front();
    m_pending_id.pop();
    return true;
  }

  rgrid_t    rgrid;
  State      state;

  std::atomic<int32_t>  failures;
  std::atomic<size_t>   total_ranges;
  // int32_t resource;
  
  private:
  client::Host::Ptr m_queue = nullptr;
  std::queue<client::ConnQueue::ReqBase::Ptr> m_pending_id;

};
typedef std::vector<Ranger::Ptr>  RangerList;

}}

#endif // swc_manager_Ranger_h