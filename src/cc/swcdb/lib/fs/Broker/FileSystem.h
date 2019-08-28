/*
 * Copyright (C) 2019 SWC-DB (author: Kashirin Alex (kashirin.alex@gmail.com))
 */

#ifndef swc_lib_fs_Broker_FileSystem_h
#define swc_lib_fs_Broker_FileSystem_h

#include "swcdb/lib/fs/FileSystem.h"

#include "Protocol/Commands.h"
#include "Protocol/req/Exists.h"
#include "Protocol/req/Remove.h"
#include "Protocol/req/Length.h"
#include "Protocol/req/Mkdirs.h"
#include "Protocol/req/Readdir.h"
#include "Protocol/req/Rmdir.h"
#include "Protocol/req/Create.h"
#include "Protocol/req/Append.h"
#include "Protocol/req/Open.h"
#include "Protocol/req/Read.h"
#include "Protocol/req/Pread.h"
#include "Protocol/req/Seek.h"
#include "Protocol/req/Sync.h"
#include "Protocol/req/Flush.h"
#include "Protocol/req/Close.h"

#include "swcdb/lib/core/comm/SerializedClient.h"
#include "AppContext.h"

namespace SWC{ namespace FS {

bool apply_broker();


class FileSystemBroker: public FileSystem {
  public:

  static const EndPoints get_endpoints(){
    std::string host = Env::Config::settings()->get<String>(
      "swc.fs.broker.host", "");
    if(host.empty()){
      char hostname[256];
      gethostname(hostname, sizeof(hostname));
      host.append(hostname);
    }
    Strings addr;
    return Resolver::get_endpoints(
      Env::Config::settings()->get<int32_t>("swc.fs.broker.port"),
      addr, host, true
    );
  }

  FileSystemBroker()
    : FileSystem(apply_broker()),
      m_io(std::make_shared<IoContext>("FsBroker",
        Env::Config::settings()->get<int32_t>("swc.fs.broker.handlers"))),
      m_service(std::make_shared<client::SerializedClient>(
        "FS-BROKER", m_io->shared(), std::make_shared<FsClientAppCtx>())),
      m_type_underlying(parse_fs_type(
        Env::Config::settings()->get<String>("swc.fs.broker.underlying"))),
      cfg_timeout(Env::Config::settings()->get_ptr<gInt32t>(
        "swc.fs.broker.timeout")),
      cfg_timeout_ratio(Env::Config::settings()->get_ptr<gInt32t>(
        "swc.fs.broker.timeout.bytes.ratio")),
      m_endpoints(get_endpoints()),
      m_run(true) { 
        
    m_io->run(m_io);
  }

  virtual ~FileSystemBroker(){}

  void stop() override {
    m_run = false;
    m_service->stop();
    m_io->stop();
  }

  Types::Fs get_type() override {
    return m_type_underlying;
  }

  const std::string to_string() override {
    return format("(type=BROKER, underlying-type=%s)", 
                    type_to_string(m_type_underlying).c_str());
  }


  bool send_request(Protocol::Req::ReqBasePtr hdlr){

    client::ClientConPtr conn = nullptr;
    do {
      conn = m_service->get_connection(
        m_endpoints, std::chrono::milliseconds(20000), 3);
    
      if(!m_run) {
        hdlr->error = Error::SERVER_SHUTTING_DOWN;
        return true;
      }
    } while(conn == nullptr);

    if(conn->send_request(hdlr->cbp, hdlr) != Error::OK) 
      return false;

    m_service->preserve(conn);
    return true;
  }

  void send_request_sync(Protocol::Req::ReqBasePtr hdlr, 
                         std::promise<void> res){
    while(!send_request(hdlr));
    if(m_run)
      res.get_future().wait();
  }

  /// File/Dir name actions

  bool exists(int &err, const String &name) override {
    Protocol::Req::ExistsPtr hdlr = std::make_shared<Protocol::Req::Exists>(
      cfg_timeout->get(), name);
    
    send_request_sync(hdlr, hdlr->promise());
    err = hdlr->error;
    return hdlr->state;
  }

  void exists(Callback::ExistsCb_t cb, const String &name) override {
    Protocol::Req::ExistsPtr hdlr = std::make_shared<Protocol::Req::Exists>(
      cfg_timeout->get(), name, cb);
      
    while(!send_request(hdlr));
  }

  void remove(int &err, const String &name) override {
    Protocol::Req::RemovePtr hdlr = std::make_shared<Protocol::Req::Remove>(
      cfg_timeout->get(), name);

    send_request_sync(hdlr, hdlr->promise());
    err = hdlr->error;
  }

  void remove(Callback::RemoveCb_t cb, const String &name) override {
    Protocol::Req::RemovePtr hdlr = std::make_shared<Protocol::Req::Remove>(
      cfg_timeout->get(), name, cb);
      
    while(!send_request(hdlr));
  }
  
  size_t length(int &err, const String &name) override {
    Protocol::Req::LengthPtr hdlr = std::make_shared<Protocol::Req::Length>(
      cfg_timeout->get(), name);

    send_request_sync(hdlr, hdlr->promise());
    err = hdlr->error;
    return hdlr->length;
  }

  void length(Callback::LengthCb_t cb, const String &name) override {
    Protocol::Req::LengthPtr hdlr = std::make_shared<Protocol::Req::Length>(
      cfg_timeout->get(), name, cb);
      
    while(!send_request(hdlr));
  }

  void mkdirs(int &err, const String &name) override {
    Protocol::Req::MkdirsPtr hdlr = std::make_shared<Protocol::Req::Mkdirs>(
      cfg_timeout->get(), name);

    send_request_sync(hdlr, hdlr->promise());
    err = hdlr->error;
  }

  void mkdirs(Callback::MkdirsCb_t cb, const String &name) override {
    Protocol::Req::MkdirsPtr hdlr = std::make_shared<Protocol::Req::Mkdirs>(
      cfg_timeout->get(), name, cb);
      
    while(!send_request(hdlr));
  }

  void readdir(int &err, const String &name, DirentList &results) override {
    Protocol::Req::ReaddirPtr hdlr = std::make_shared<Protocol::Req::Readdir>(
      cfg_timeout->get(), name);

    send_request_sync(hdlr, hdlr->promise());
    err = hdlr->error;
    results = hdlr->listing;
  }

  void readdir(Callback::ReaddirCb_t cb, const String &name) override {
    Protocol::Req::ReaddirPtr hdlr = std::make_shared<Protocol::Req::Readdir>(
      cfg_timeout->get(), name, cb);
      
    while(!send_request(hdlr));
  }

  void rmdir(int &err, const String &name) override {
    Protocol::Req::RmdirPtr hdlr = std::make_shared<Protocol::Req::Rmdir>(
      cfg_timeout->get(), name);

    send_request_sync(hdlr, hdlr->promise());
    err = hdlr->error;
  }

  void rmdir(Callback::RmdirCb_t cb, const String &name) override {
    Protocol::Req::RmdirPtr hdlr = std::make_shared<Protocol::Req::Rmdir>(
      cfg_timeout->get(), name, cb);
      
    while(!send_request(hdlr));
  }

  /// SmartFd actions

  void create(int &err, SmartFdPtr &smartfd,
              int32_t bufsz, int32_t replication, int64_t blksz) override {
    Protocol::Req::CreatePtr hdlr = std::make_shared<Protocol::Req::Create>(
      cfg_timeout->get(), smartfd, bufsz, replication, blksz);

    send_request_sync(hdlr, hdlr->promise());
    err = hdlr->error;
  }

  void create(Callback::CreateCb_t cb, SmartFdPtr &smartfd,
              int32_t bufsz, int32_t replication, int64_t blksz) override {
    Protocol::Req::CreatePtr hdlr = std::make_shared<Protocol::Req::Create>(
      cfg_timeout->get(), smartfd, bufsz, replication, blksz, cb);
      
    while(!send_request(hdlr));
  }
  
  size_t append(int &err, SmartFdPtr &smartfd, 
                StaticBuffer &buffer, Flags flags) override {
    Protocol::Req::AppendPtr hdlr = std::make_shared<Protocol::Req::Append>(
      cfg_timeout->get()+buffer.size/cfg_timeout_ratio->get(), 
      smartfd, buffer, flags);

    send_request_sync(hdlr, hdlr->promise());
    err = hdlr->error;
    return hdlr->amount;
  }
   
  void append(Callback::AppendCb_t cb, SmartFdPtr &smartfd, 
              StaticBuffer &buffer, Flags flags) override {
    Protocol::Req::AppendPtr hdlr = std::make_shared<Protocol::Req::Append>(
      cfg_timeout->get()+buffer.size/cfg_timeout_ratio->get(), 
      smartfd, buffer, flags, cb);
      
    while(!send_request(hdlr));
  }

  void open(int &err, SmartFdPtr &smartfd, int32_t bufsz) override {
    Protocol::Req::OpenPtr hdlr = std::make_shared<Protocol::Req::Open>(
      cfg_timeout->get(), smartfd, bufsz);

    send_request_sync(hdlr, hdlr->promise());
    err = hdlr->error;
  }

  void open(Callback::OpenCb_t cb, SmartFdPtr &smartfd, 
            int32_t bufsz) override {
    Protocol::Req::OpenPtr hdlr = std::make_shared<Protocol::Req::Open>(
      cfg_timeout->get(), smartfd, bufsz, cb);
      
    while(!send_request(hdlr));
  }
  
  size_t read(int &err, SmartFdPtr &smartfd, 
              void *dst, size_t amount) override {
    Protocol::Req::ReadPtr hdlr = std::make_shared<Protocol::Req::Read>(
      cfg_timeout->get()+amount/cfg_timeout_ratio->get(), 
      smartfd, dst, amount);

    send_request_sync(hdlr, hdlr->promise());
    err = hdlr->error;
    return hdlr->amount;
  }
   
  void read(Callback::ReadCb_t cb, SmartFdPtr &smartfd, 
            size_t amount) override {
    Protocol::Req::ReadPtr hdlr = std::make_shared<Protocol::Req::Read>(
      cfg_timeout->get()+amount/cfg_timeout_ratio->get(), 
      smartfd, nullptr, amount, cb);
      
    while(!send_request(hdlr));
  }
  
  size_t pread(int &err, SmartFdPtr &smartfd, 
              uint64_t offset, void *dst, size_t amount) override {
    Protocol::Req::PreadPtr hdlr = std::make_shared<Protocol::Req::Pread>(
      cfg_timeout->get()+amount/cfg_timeout_ratio->get(), 
      smartfd, offset, dst, amount);

    send_request_sync(hdlr, hdlr->promise());
    err = hdlr->error;
    return hdlr->amount;
  }
   
  void pread(Callback::ReadCb_t cb, SmartFdPtr &smartfd, 
            uint64_t offset, size_t amount) override {
    Protocol::Req::PreadPtr hdlr = std::make_shared<Protocol::Req::Pread>(
      cfg_timeout->get()+amount/cfg_timeout_ratio->get(), 
      smartfd, offset, nullptr, amount, cb);
      
    while(!send_request(hdlr));
  }

  void seek(int &err, SmartFdPtr &smartfd, size_t offset) override {
    Protocol::Req::SeekPtr hdlr = std::make_shared<Protocol::Req::Seek>(
      cfg_timeout->get(), smartfd, offset);

    send_request_sync(hdlr, hdlr->promise());
    err = hdlr->error;
  }
   
  void seek(Callback::SeekCb_t cb, SmartFdPtr &smartfd, 
            size_t offset) override {
    Protocol::Req::SeekPtr hdlr = std::make_shared<Protocol::Req::Seek>(
      cfg_timeout->get(), smartfd, offset, cb);
      
    while(!send_request(hdlr));
  }

  void flush(int &err, SmartFdPtr &smartfd) override {
    Protocol::Req::FlushPtr hdlr = std::make_shared<Protocol::Req::Flush>(
      cfg_timeout->get(), smartfd);

    send_request_sync(hdlr, hdlr->promise());
    err = hdlr->error;
  }
  
  void flush(Callback::FlushCb_t cb, SmartFdPtr &smartfd) override {
    Protocol::Req::FlushPtr hdlr = std::make_shared<Protocol::Req::Flush>(
      cfg_timeout->get(), smartfd, cb);
      
    while(!send_request(hdlr));
  }

  void sync(int &err, SmartFdPtr &smartfd) override {
    Protocol::Req::SyncPtr hdlr = std::make_shared<Protocol::Req::Sync>(
      cfg_timeout->get(), smartfd);

    send_request_sync(hdlr, hdlr->promise());
    err = hdlr->error;
  }
  
  void sync(Callback::SyncCb_t cb, SmartFdPtr &smartfd) override {
    Protocol::Req::SyncPtr hdlr = std::make_shared<Protocol::Req::Sync>(
      cfg_timeout->get(), smartfd, cb);
      
    while(!send_request(hdlr));
  }

  void close(int &err, SmartFdPtr &smartfd) override {
    Protocol::Req::ClosePtr hdlr = std::make_shared<Protocol::Req::Close>(
      cfg_timeout->get(), smartfd);

    send_request_sync(hdlr, hdlr->promise());
    err = hdlr->error;
  }

  void close(Callback::CreateCb_t cb, SmartFdPtr &smartfd) override {
    Protocol::Req::ClosePtr hdlr = std::make_shared<Protocol::Req::Close>(
      cfg_timeout->get(), smartfd, cb);
      
    while(!send_request(hdlr));
  }

  //



  private:

  IoContextPtr      m_io;
  client::ClientPtr m_service = nullptr;
  Types::Fs         m_type_underlying;
  const EndPoints   m_endpoints;
  std::atomic<bool> m_run;

  const gInt32tPtr cfg_timeout;
  const gInt32tPtr cfg_timeout_ratio;
};


}}


extern "C" {
SWC::FS::FileSystem* fs_make_new_broker();
void fs_apply_cfg_broker(SWC::Env::ConfigPtr env);
}

#endif  // swc_lib_fs_Broker_FileSystem_h