/*
 * Copyright (C) 2019 SWC-DB (author: Kashirin Alex (kashirin.alex@gmail.com))
 */


#ifndef swc_core_comm_SerializedClient_h
#define swc_core_comm_SerializedClient_h

#include <chrono>
#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <unordered_map>

#include "AppContext.h"
#include "ConnHandlerClient.h"


namespace SWC { namespace client {

typedef ConnHandlerClientPtr ClientConPtr;
typedef std::function<void(ClientConPtr)> NewClientConnCb_t;

static std::string to_string(ClientConPtr conn){
  std::string s("Connection");

  if(!conn->is_open()) {
    s.append(" CLOSED");
    return s;
  }

  s.append(" remote=");
  try{
    s.append(conn->endpoint_remote_str());
    s.append(" (hash=");
    s.append(std::to_string(conn->endpoint_remote_hash()));
    s.append(")");
  } catch(...){
    s.append("Exception");
  }
  try{
    s.append(" local=");
    s.append(conn->endpoint_local_str());
    s.append(" (hash=");
    s.append(std::to_string(conn->endpoint_local_hash()));
    s.append(")");
  } catch(...){
    s.append("Exception");
  }
  return s;
}
  

class ServerConnections : public std::enable_shared_from_this<ServerConnections> {
  public:

  ServerConnections(std::string srv_name, const EndPoint endpoint,
                    IOCtxPtr ioctx, AppContextPtr ctx)
                  : m_srv_name(srv_name), m_endpoint(endpoint), 
                    m_ioctx(ioctx), m_ctx(ctx){}

  virtual ~ServerConnections(){}

  void reusable(ClientConPtr &conn) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if(m_conns.empty())
      return;
    conn = m_conns.front();
    m_conns.pop();
    if(conn->is_open())
      HT_DEBUGF("Reusing connection: %s, %s", 
                m_srv_name.c_str(), to_string(conn).c_str());
    else
      conn = nullptr;
  }

  void connection(ClientConPtr &conn, std::chrono::milliseconds timeout){
    
    reusable(conn);
    if(conn != nullptr)
      return;

    HT_DEBUGF("Connecting: %s, addr=[%s]:%d", m_srv_name.c_str(), 
              m_endpoint.address().to_string().c_str(), m_endpoint.port());
    
    SocketPtr s = std::make_shared<asio::ip::tcp::socket>(*m_ioctx.get());
    asio::error_code ec;
    s->open(m_endpoint.protocol(), ec);
    if(ec || !s->is_open())
      return;

    s->connect(m_endpoint, ec);
    if(ec || !s->is_open())
      return;

    conn = std::make_shared<ConnHandlerClient>(m_ctx, s, m_ioctx);
    conn->new_connection();
    HT_DEBUGF("New connection: %s, %s", 
              m_srv_name.c_str(), to_string(conn).c_str());
  }
  
  void connection(std::chrono::milliseconds timeout, NewClientConnCb_t cb){

    HT_DEBUGF("Connecting: %s, addr=[%s]:%d", m_srv_name.c_str(), 
              m_endpoint.address().to_string().c_str(), m_endpoint.port());
    
    SocketPtr s = std::make_shared<asio::ip::tcp::socket>(*m_ioctx.get());
    s->async_connect(m_endpoint, 
      [s, cb, ptr=shared_from_this()]
      (const std::error_code& ec){
        if(ec || !s->is_open()){
          cb(nullptr);
        } else {
          ClientConPtr conn 
            = std::make_shared<ConnHandlerClient>(ptr->m_ctx, s, ptr->m_ioctx);
          HT_DEBUGF("New connection: %s, %s", 
                    ptr->m_srv_name.c_str(), to_string(conn).c_str());

          conn->new_connection();
          cb(conn);
        }
      }
    );       
  }

  void put_back(ClientConPtr conn){
    std::lock_guard<std::mutex> lock(m_mutex);
    m_conns.push(conn);
  }
  
  bool empty(){
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_conns.empty();
  }

  void close_all(){
    std::lock_guard<std::mutex> lock(m_mutex);
    while(!m_conns.empty()){
      m_conns.front()->close();
      m_conns.pop();
    }
  }

  private:

  const std::string m_srv_name;
  const EndPoint    m_endpoint;
  IOCtxPtr          m_ioctx;
  AppContextPtr     m_ctx;
  std::mutex        m_mutex;
  std::queue<ClientConPtr> m_conns;

};

typedef std::shared_ptr<ServerConnections> ServerConnectionsPtr;
typedef std::unordered_map<size_t, ServerConnectionsPtr> ServerConnectionsMap;

class SerializedClient{

  public:

  SerializedClient(std::string srv_name, IOCtxPtr ioctx, AppContextPtr ctx)
                  : m_srv_name(srv_name), m_ioctx(ioctx), m_ctx(ctx), 
                    m_run(true) {
    HT_INFOF("Init: %s", m_srv_name.c_str());
  }
  ServerConnectionsPtr get_srv(EndPoint endpoint) {
    size_t hash = endpoint_hash(endpoint);
    std::lock_guard<std::mutex> lock(m_mutex);

    auto it = m_srv_conns.find(hash);
    if(it != m_srv_conns.end())
      return (*it).second;

    ServerConnectionsPtr srv = std::make_shared<ServerConnections>(
      m_srv_name, endpoint, m_ioctx, m_ctx);
    m_srv_conns.insert(std::make_pair(hash, srv));
    return srv;
  }

  ClientConPtr get_connection(
        const EndPoints endpoints, 
        std::chrono::milliseconds timeout = std::chrono::milliseconds(0),
        uint32_t probes=0
        ){
    
    ClientConPtr conn = nullptr;
    if(endpoints.empty()){
      HT_WARNF("get_connection: %s, Empty-Endpoints", m_srv_name.c_str());
      return conn;
    }

    uint32_t tries = probes;
    do {
      HT_DEBUGF("get_connection: %s, tries=%d", m_srv_name.c_str(), tries);

      for(auto endpoint : endpoints){
        get_srv(endpoint)->connection(conn, timeout);
        if(conn != nullptr)
          return conn;
      }
      
      std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    } while (m_run.load() && (probes == 0 || --tries > 0));

    return conn;
  }

  void get_connection(
        const EndPoints endpoints, 
        NewClientConnCb_t cb,
        std::chrono::milliseconds timeout = std::chrono::milliseconds(0),
        uint32_t probes=0){
    
    if(endpoints.empty()){
      HT_WARNF("get_connection: %s, Empty-Endpoints", m_srv_name.c_str());
      cb(nullptr);
      return;
    }

    get_connection(endpoints, cb, timeout, probes, probes, 0);
  }
  
  void get_connection(
        const EndPoints endpoints, 
        NewClientConnCb_t cb,
        std::chrono::milliseconds timeout,
        uint32_t probes, uint32_t tries, 
        int next){
          
    HT_DEBUGF("get_connection: %s, tries=%d", m_srv_name.c_str(), tries);
    if(next == endpoints.size())
      next = 0;

    ServerConnectionsPtr srv = get_srv(endpoints.at(next++));
    ClientConPtr conn = nullptr;
    srv->reusable(conn);
    if(conn != nullptr) {
      cb(conn);
      return;
    }
    
    srv->connection(timeout, 
      [this, endpoints, cb, timeout, probes, tries, next]
      (ClientConPtr conn){
        if(conn != nullptr && conn->is_open()){
          cb(conn);
          return;
        }
        if(m_run.load() && (probes == 0 || tries-1 > 0)){
          std::this_thread::sleep_for(std::chrono::milliseconds(5000));
          get_connection(endpoints, cb, timeout, probes, tries-1, next);
          return;
        }
        cb(nullptr);
      });
  }

  void preserve(ClientConPtr conn){
    size_t hash = conn->endpoint_remote_hash();

    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_srv_conns.find(hash);
    if(it != m_srv_conns.end())
      (*it).second->put_back(conn);
  }

  void close(ClientConPtr conn){
    size_t hash = conn->endpoint_remote_hash();
    conn->do_close();

    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_srv_conns.find(hash);
    if(it != m_srv_conns.end() && (*it).second->empty())
      m_srv_conns.erase(it);
  }

  std::string to_str(ClientConPtr conn){
    std::string s(m_srv_name);
    s.append(" ");
    s.append(to_string(conn));
    return s;
  }
  
  void stop(){
    m_run.store(false);
    
    std::lock_guard<std::mutex> lock(m_mutex);
    ServerConnectionsMap::iterator it;
    while((it = m_srv_conns.begin()) != m_srv_conns.end()){
      it->second->close_all();
      m_srv_conns.erase(it);
    }
    HT_INFOF("Stop: %s", m_srv_name.c_str());
  }

  virtual ~SerializedClient(){}

  private:
  const std::string     m_srv_name;
  IOCtxPtr              m_ioctx;
  AppContextPtr         m_ctx;

  std::mutex            m_mutex;
  ServerConnectionsMap  m_srv_conns;
  std::atomic<bool>     m_run;

};


typedef std::shared_ptr<SerializedClient> ClientPtr;

}}

#endif // swc_core_comm_SerializedClient_h