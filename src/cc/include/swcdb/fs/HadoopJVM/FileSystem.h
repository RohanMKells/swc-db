/*
 * SWC-DB© Copyright since 2019 Alex Kashirin <kashirin.alex@gmail.com>
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */

#ifndef swc_fs_HadoopJVM_FileSystem_h
#define swc_fs_HadoopJVM_FileSystem_h

#include "swcdb/fs/FileSystem.h"
#include <hdfs.h>

namespace SWC { namespace FS {

Configurables apply_hadoop_jvm();



class FileSystemHadoopJVM final : public FileSystem {
  public:

  struct Service {
    typedef std::shared_ptr<Service> Ptr;
    
    Service(hdfsFS srv) : srv(srv) { }

    ~Service() { if(srv) hdfsDisconnect(srv); }

    hdfsFS  srv;
  };

  FileSystemHadoopJVM();

  virtual ~FileSystemHadoopJVM();

  Type get_type() override;

  std::string to_string() override;

  void stop() override;

  Service::Ptr setup_connection();

  bool initialize(Service::Ptr& fs);

  Service::Ptr get_fs(int& err);

  void need_reconnect(int& err, Service::Ptr& fs);


  bool exists(int& err, const std::string& name) override;
  
  void remove(int& err, const std::string& name) override;

  size_t length(int& err, const std::string& name) override;

  void mkdirs(int& err, const std::string& name) override;

  void readdir(int& err, const std::string& name, 
                DirentList& results) override;

  void rmdir(int& err, const std::string& name) override;

  void rename(int& err, const std::string& from, 
                        const std::string& to)  override;

  void create(int& err, SmartFd::Ptr& smartfd, 
              int32_t bufsz, uint8_t replication, int64_t blksz) override;

  void open(int& err, SmartFd::Ptr& smartfd, int32_t bufsz = -1) override;
  
  size_t read(int& err, SmartFd::Ptr& smartfd, 
              void *dst, size_t amount) override;

  size_t pread(int& err, SmartFd::Ptr& smartfd, 
               uint64_t offset, void *dst, size_t amount) override;

  size_t append(int& err, SmartFd::Ptr& smartfd, 
                StaticBuffer& buffer, Flags flags) override;

  void seek(int& err, SmartFd::Ptr& smartfd, size_t offset) override;

  void flush(int& err, SmartFd::Ptr& smartfd) override;

  void sync(int& err, SmartFd::Ptr& smartfd) override;

  void close(int& err, SmartFd::Ptr& smartfd) override;

  private:

  struct SmartFdHadoopJVM final : public SmartFd {
    public:
  
    typedef std::shared_ptr<SmartFdHadoopJVM> Ptr;
  
    static Ptr make_ptr(const std::string& filepath, uint32_t flags);

    static Ptr make_ptr(SmartFd::Ptr& smart_fd);

    SmartFdHadoopJVM(const std::string& filepath, uint32_t flags,
                     int32_t fd=-1, uint64_t pos=0);

    virtual ~SmartFdHadoopJVM();

    hdfsFile file() const;

    void file(const hdfsFile& file);

    private:

    hdfsFile m_file;
  };

  SmartFdHadoopJVM::Ptr get_fd(SmartFd::Ptr& smartfd);

  std::atomic<bool>       m_run;
  std::atomic<int32_t>    m_nxt_fd;
  
  std::mutex              m_mutex;
  std::condition_variable m_cv;
  bool                    m_connecting;

  Service::Ptr            m_fs;
  
  int hdfs_cfg_min_blk_sz = 1048576;
};


}}



extern "C" { 
SWC::FS::FileSystem* fs_make_new_hadoop_jvm();
void fs_apply_cfg_hadoop_jvm(SWC::Env::Config::Ptr env);
}

#ifdef SWC_IMPL_SOURCE
#include "swcdb/fs/HadoopJVM/FileSystem.cc"
#endif 


#endif  // swc_fs_HadoopJVM_FileSystem_h