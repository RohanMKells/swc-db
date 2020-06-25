/*
 * Copyright Since 2019 SWC-DB© [author: Kashirin Alex kashirin.alex@gmail.com]
 */

#ifndef swc_fs_Dirent_h
#define swc_fs_Dirent_h

#include <memory>
#include <vector>

#include "swcdb/core/Serializable.h"

namespace SWC{ namespace FS {

/// Directory entry
class Dirent final : public Serializable {

  public:
  /// File or directory name
  std::string   name;
  /// Length of file
  uint64_t      length {};
  /// Last modification time
  time_t        last_modification_time {};
  /// Flag indicating if entry is a directory
  bool          is_dir {};

  std::string to_string() const;

  ~Dirent();
  
  private:

  size_t encoded_length_internal() const;

  void encode_internal(uint8_t** bufp) const;

  void decode_internal(const uint8_t** bufp, size_t* remainp);
      
};

typedef std::vector<Dirent> DirentList;
}}



#ifdef SWC_IMPL_SOURCE
#include "swcdb/fs/Dirent.cc"
#endif 


#endif  // swc_fs_Dirent_h