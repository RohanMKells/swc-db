/*
 * Copyright Since 2019 SWC-DB© [author: Kashirin Alex kashirin.alex@gmail.com]
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */


#include "swcdb/fs/Interface.h"
#include <dlfcn.h>

namespace SWC{ namespace FS {

namespace  { // local ns
void hold_delay() {
  std::this_thread::sleep_for(std::chrono::microseconds(10000));
}
}

Interface::Interface(Types::Fs typ) : m_type(typ), m_fs(use_filesystem()) {

  SWC_LOGF(LOG_INFO, "INIT-%s", to_string().c_str());
}
  
FileSystem::Ptr Interface::use_filesystem(){
  std::string fs_name;
    
  switch(m_type){

    case Types::Fs::LOCAL:{
#if defined (BUILTIN_FS_LOCAL) || defined (BUILTIN_FS_ALL)
      return std::make_shared<FileSystemLocal>();
#endif
      fs_name.append("local");
      break;
    }

    case Types::Fs::BROKER:{
#if defined (BUILTIN_FS_BROKER) || defined (BUILTIN_FS_ALL)
      return std::make_shared<FileSystemBroker>();
#endif
      fs_name.append("broker");
      break;
    }

    case Types::Fs::HADOOP: {
#if defined (BUILTIN_FS_HADOOP) || defined (BUILTIN_FS_ALL)
      return std::make_shared<FileSystemHadoop>();
#endif
      fs_name.append("hadoop");
      break;
    }

    case Types::Fs::HADOOP_JVM: {
#if defined (BUILTIN_FS_HADOOP_JVM) || defined (BUILTIN_FS_ALL)
      return std::make_shared<FileSystemHadoopJVM>();
#endif
      fs_name.append("hadoop_jvm");
      break;
    }
/* 
    case Types::Fs::CEPH:{
#if defined (BUILTIN_FS_CEPH) || defined (BUILTIN_FS_ALL)
      return std::make_shared<FileSystemCeph>();
#endif
      fs_name.append("ceph");
      break;
    }
*/
    case Types::Fs::CUSTOM: {
      fs_name.append("custom");
      break;
    }

    default:
      SWC_THROWF(Error::CONFIG_BAD_VALUE, 
        "Unimplemented FileSystem name=%s type=%d", 
        fs_name.c_str(), (int)m_type);
  }
    
  std::string fs_lib;
  if(Env::Config::settings()->has("swc.fs.lib."+fs_name)) {
    fs_lib.append(
      Env::Config::settings()->get_str("swc.fs.lib."+fs_name));
  } else {
    fs_lib.append(Env::Config::settings()->install_path);
    fs_lib.append("/lib/libswcdb_fs_"); // (./lib/libswcdb_fs_local.so)
    fs_lib.append(fs_name);
    fs_lib.append(".so");
  }

  const char* err = dlerror();
  void* handle = dlopen(fs_lib.c_str(), RTLD_NOW | RTLD_LAZY | RTLD_LOCAL);
  if (handle == NULL || err != NULL)
    SWC_THROWF(Error::CONFIG_BAD_VALUE, 
              "Shared Lib %s, open fail: %s\n", 
              fs_lib.c_str(), err);

  err = dlerror();
  std::string handler_name =  "fs_apply_cfg_"+fs_name;
  void* f_cfg_ptr = dlsym(handle, handler_name.c_str());
  if (err != NULL || f_cfg_ptr == nullptr)
    SWC_THROWF(Error::CONFIG_BAD_VALUE, 
              "Shared Lib %s, link(%s) fail: %s handle=%d\n", 
              fs_lib.c_str(), handler_name.c_str(), err, (size_t)handle);
  ((fs_apply_cfg_t*)f_cfg_ptr)(Env::Config::get());
    
  err = dlerror();
  handler_name =  "fs_make_new_"+fs_name;
  void* f_new_ptr = dlsym(handle, handler_name.c_str());
  if (err != NULL || f_new_ptr == nullptr)
    SWC_THROWF(Error::CONFIG_BAD_VALUE, 
              "Shared Lib %s, link(%s) fail: %s handle=%d\n", 
              fs_lib.c_str(), handler_name.c_str(), err, (size_t)handle);
    
  loaded_dl = {.lib=handle, .cfg=f_cfg_ptr, .make=f_new_ptr};
  return FileSystem::Ptr(((fs_make_new_t*)f_new_ptr)());
}

Interface::Ptr Interface::ptr(){ 
  return this; 
}

Interface::~Interface() {
  m_fs = nullptr;
  if(loaded_dl.lib != nullptr) {
    ((fs_apply_cfg_t*)loaded_dl.cfg)(nullptr);
    dlclose(loaded_dl.lib);
  }
}

Types::Fs Interface::get_type(){
  return m_fs->get_type();
}

FileSystem::Ptr Interface::get_fs(){
  return m_fs;
}

std::string Interface::to_string() {
  return format("FS::Interface(type=%d, details=%s)", 
                (int)m_type, m_fs==nullptr?"NULL":m_fs->to_string().c_str());
}

bool Interface::need_fds() const {
  return m_fs->need_fds();
}

void Interface::stop() { 
  m_fs->stop();
}

void Interface::get_structured_ids(int& err, const std::string& base_path, 
                                  IdEntries_t& entries, 
                                  const std::string& base_id) {
  //path(base_path) .../111/222/333/444f >> IdEntries_t{(int64_t)111222333444}
    
  DirentList dirs;
  readdir(err, base_path, dirs);
  if(err)
    return;

  for(auto& entry : dirs) {
    if(!entry.is_dir) continue;

    std::string id_name = base_id;
    if(entry.name.back() == id_split_last){
      id_name.append(entry.name.substr(0, entry.name.length()-1));
      try {
        entries.push_back((int64_t)strtoll(id_name.c_str(), NULL, 0));
      } catch(...){
        SWC_LOGF(LOG_ERROR, "Error converting id_name=%s to int64", id_name.c_str());
      }
      continue;
    }
      
    std::string new_base_path = base_path;
    new_base_path.append("/");
    new_base_path.append(entry.name);
    id_name.append(entry.name);
    get_structured_ids(err, new_base_path, entries, id_name);
    if(err)
      return;
  }
}
  
// default form to FS methods

void Interface::readdir(int& err, const std::string& base_path, 
                        DirentList& dirs) {
  for(;;) {
    DirentList found_dirs;
    m_fs->readdir(err = Error::OK, base_path, found_dirs);
    switch(err) {
      case Error::OK:
      case EACCES:
      case ENOENT:
      case Error::SERVER_SHUTTING_DOWN: {
        dirs = found_dirs;
        return;
      }
      default:
        hold_delay();
        SWC_LOGF(LOG_WARN, "readdir, retrying to err=%d(%s)",
                  err, Error::get_text(err));
    }
  }
}

bool Interface::exists(int& err, const std::string& name) {
  for(bool state;;) {
    state = m_fs->exists(err = Error::OK, name);
    switch(err) {
      case Error::OK:
      case Error::SERVER_SHUTTING_DOWN:
        return state;
      default:
        hold_delay();
        SWC_LOGF(LOG_WARN, "exists, retrying to err=%d(%s)",
                  err, Error::get_text(err));
    }
  }
}

void Interface::exists(const Callback::ExistsCb_t& cb, 
                       const std::string& name) {
  Callback::ExistsCb_t cb_wrapper; 
  cb_wrapper = [cb, name, &cb_wrapper, ptr=ptr()]
    (int err, bool state) { 
      if(!err || err == Error::SERVER_SHUTTING_DOWN) 
        cb(err, state);
      else 
        ptr->get_fs()->exists(cb_wrapper, name);
    };
  m_fs->exists(cb_wrapper, name);
}

void Interface::mkdirs(int& err, const std::string& name) {
  for(;;) {
    m_fs->mkdirs(err = Error::OK, name);
    switch(err) {
      case Error::OK:
      case EEXIST:
      case Error::SERVER_SHUTTING_DOWN:
        return;
      default:
        hold_delay();
        SWC_LOGF(LOG_WARN, "mkdirs, retrying to err=%d(%s)",
                  err, Error::get_text(err));
    }
  }
}

void Interface::rmdir(int& err, const std::string& name) {
  for(;;) {
    m_fs->rmdir(err = Error::OK, name);
    switch(err) {
      case Error::OK:
      case EACCES:
      case ENOENT:
      case Error::SERVER_SHUTTING_DOWN:
        return;
      default:
        hold_delay();
        SWC_LOGF(LOG_WARN, "rmdir, retrying to err=%d(%s)",
                  err, Error::get_text(err));
    }
  }
}

void Interface::rmdir_incl_opt_subs(int& err, const std::string& name, 
                                    const std::string& up_to) {
  rmdir(err, name);
  if(err)
    return;

  const char* p=name.data();
  std::string base_path;
  for(const char* c=p+name.length(); c>p; --c) {
    if(*c != '/')
      continue;
    base_path = std::string(p, c-p);
    if(up_to.compare(base_path) == 0)
      break;

    DirentList entrs;
    readdir(err, base_path, entrs);
    if(!err && !entrs.size()) {
      rmdir(err, base_path);
      if(!err)
        continue;
    }
    break;
  }
  if(err)
    err = Error::OK;
}

void Interface::remove(int& err, const std::string& name) {
  for(;;) {
    m_fs->remove(err = Error::OK, name);
    switch(err) {
      case Error::OK:
      case EACCES:
      case ENOENT:
      case Error::SERVER_SHUTTING_DOWN:
        return;
      default:
        hold_delay();
        SWC_LOGF(LOG_WARN, "remove, retrying to err=%d(%s)",
                  err, Error::get_text(err));
    }
  }
}
  
void Interface::rename(int& err, const std::string& from , 
                       const std::string& to) {
  for(;;) {
    m_fs->rename(err = Error::OK, from, to);
    switch(err) {
      case Error::OK:
      case EACCES:
      case ENOENT:
      case Error::SERVER_SHUTTING_DOWN:
        return;
      default:
        hold_delay();
        SWC_LOGF(LOG_WARN, "rename, retrying to err=%d(%s)", 
                  err, Error::get_text(err));
    }
  }
} 

size_t Interface::length(int& err, const std::string& name) {
  for(size_t length;;) {
    length = m_fs->length(err = Error::OK, name);
    switch(err) {
      case Error::OK:
      case Error::FS_PATH_NOT_FOUND:
      //case Error::FS_PERMISSION_DENIED:
      case Error::SERVER_SHUTTING_DOWN:
        return length;
      default:
        hold_delay();
        SWC_LOGF(LOG_WARN, "length, retrying to err=%d(%s)", 
                  err, Error::get_text(err));
    }
  }
}


void Interface::write(int& err, SmartFd::Ptr smartfd,
                      uint8_t replication, int64_t blksz, 
                      StaticBuffer& buffer) {
  for(buffer.own=false;;) {
    m_fs->write(err = Error::OK, smartfd, replication, blksz, buffer);
    switch(err) {
      case Error::OK:
      case Error::FS_PATH_NOT_FOUND:
      //case Error::FS_PERMISSION_DENIED:
      case Error::SERVER_SHUTTING_DOWN: {
        buffer.own=true;
        return;
      }
      default:
        hold_delay();
        SWC_LOGF(LOG_WARN, "write, retrying to err=%d(%s)", 
                err, Error::get_text(err));
    }
  }
}
    
void Interface::read(int& err, const std::string& name, StaticBuffer* dst) {
  for(;;) {
    m_fs->read(err = Error::OK, name, dst);
    switch(err) {
      case Error::OK:
      case Error::FS_EOF:
      case Error::FS_PATH_NOT_FOUND:
      //case Error::FS_PERMISSION_DENIED:
      case Error::SERVER_SHUTTING_DOWN: 
        return;
      default:
        hold_delay();
        SWC_LOGF(LOG_WARN, "read-all, retrying to err=%d(%s)", 
                err, Error::get_text(err));
    }
  }
}

bool Interface::open(int& err, SmartFd::Ptr& smartfd) {
  m_fs->open(err = Error::OK, smartfd);
  switch(err) {
    case Error::OK:
    case Error::FS_PATH_NOT_FOUND:
    //case Error::FS_PERMISSION_DENIED:
    case Error::SERVER_SHUTTING_DOWN:
      return false;
    default:
      if(smartfd->valid()) {
        int tmperr = Error::OK;
        m_fs->close(tmperr, smartfd);
      }
    return true;
  }
}
  
bool Interface::create(int& err, SmartFd::Ptr& smartfd,
                       int32_t bufsz, uint8_t replication, int64_t blksz) {
  m_fs->create(err = Error::OK, smartfd, bufsz, replication, blksz);
  switch(err) {
    case Error::OK:
    case Error::FS_PATH_NOT_FOUND:
    //case Error::FS_PERMISSION_DENIED:
    case Error::SERVER_SHUTTING_DOWN:
      return false;
    default:
      if(smartfd->valid()) {
        int tmperr = Error::OK;
        m_fs->close(tmperr, smartfd);
      }
    return true;
  }
}

void Interface::close(int& err, SmartFd::Ptr smartfd) {
  while(smartfd->valid()) {
    m_fs->close(err = Error::OK, smartfd);
    switch(err) {
      case Error::OK:
      case EACCES:
      case ENOENT:
      case EBADR:
      case EBADF:
      case Error::FS_BAD_FILE_HANDLE:
      case Error::SERVER_SHUTTING_DOWN:
        return;
      default:
        hold_delay();
        SWC_LOGF(LOG_WARN, "close, retrying to err=%d(%s)", 
                 err, Error::get_text(err));
    }
  }
}



void set_structured_id(const std::string& number, std::string& s) {
  if(number.length() <= id_split_len) {
    s.append(number);
    s.append({id_split_last});
  } else {
    int len = number.length()-id_split_len;
    int n=0;
    for(; n<len;){
      s.append(std::string(number, n, id_split_len));
      s.append("/");
      n += id_split_len;
    }
    s.append(std::string(number, n, id_split_len));
    s.append({id_split_last});
  }
}

} // namespace FS


namespace Env {

void FsInterface::init(Types::Fs typ) {
  m_env = std::make_shared<FsInterface>(typ);
}

FsInterface::Ptr FsInterface::get(){
  return m_env;
}

FS::Interface::Ptr FsInterface::interface(){
  SWC_ASSERT(m_env != nullptr);
  return m_env->m_interface;
}

FS::FileSystem::Ptr FsInterface::fs(){
  SWC_ASSERT(m_env != nullptr);
  return m_env->m_interface->get_fs();
}

void FsInterface::reset() {
  m_env = nullptr;
}

FsInterface::FsInterface(Types::Fs typ) 
                        : m_interface(new FS::Interface(typ)) {}

FsInterface::~FsInterface(){
  if(m_interface != nullptr)
    delete m_interface;
}
}

} // namespace SWC