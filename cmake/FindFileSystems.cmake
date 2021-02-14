#
# SWC-DB© Copyright since 2019 Alex Kashirin <kashirin.alex@gmail.com>
# License details at <https://github.com/kashirin-alex/swc-db/#license>




if(NOT SWC_BUILD_PKG OR SWC_BUILD_PKG STREQUAL "lib-fs-ceph")
SET_DEPS(
  NAME      "CEPH"
  LIB_PATHS
  INC_PATHS
  STATIC    libcephfs.a
  SHARED    cephfs
  INCLUDE   cephfs/libcephfs.h
)
endif()
#########


if(NOT SWC_BUILD_PKG OR SWC_BUILD_PKG STREQUAL "lib-fs-hadoop-jvm")
set(hadoop_home)
if(HADOOP_INSTALL_PATH)
  set(hadoop_home ${HADOOP_INSTALL_PATH})
elseif(HADOOP_COMMON_HOME)
  set(hadoop_home ${HADOOP_COMMON_HOME})
else()
  set(hadoop_home $ENV{HADOOP_HOME})
endif()


SET_DEPS(
  NAME "HADOOP_JVM"
  LIB_PATHS ${hadoop_home}/lib/native
  INC_PATHS ${hadoop_home}/include
  STATIC    libhdfs.a
  SHARED    hdfs
  INCLUDE   hdfs.h
)
endif()
###########


if(NOT SWC_BUILD_PKG OR SWC_BUILD_PKG STREQUAL "lib-fs-hadoop")
SET_DEPS(
  NAME      "HADOOP"
  LIB_PATHS ${hadoop_home}/lib/native
  INC_PATHS ${hadoop_home}/include
  STATIC    libhdfspp.a
  SHARED    hdfspp
  INCLUDE   hdfspp/hdfspp.h
)
if(HADOOP_FOUND)
  SET_DEPS(
    NAME      "PROTOBUF"
    REQUIRED  TRUE
    LIB_PATHS ""
    INC_PATHS ""
    STATIC    libprotobuf.a
    SHARED    protobuf
    INCLUDE   google/protobuf/stubs/common.h
  )
  SET_DEPS(
    NAME      "GSASL"
    REQUIRED  TRUE
    LIB_PATHS ""
    INC_PATHS ""
    STATIC    libgsasl.a
    SHARED    gsasl
    INCLUDE   gsasl.h
  )
  if(HADOOP_VERSION)
    # Library is different over versions and protobuf related
    # at setup symlink libswcdb_fs_hadoop.so to specific libswcdb_fs_hadoop_VERSION.so
    message("       Building Version: ${HADOOP_VERSION}")
  else()
    message("       Building Version: 'default' set -DHADOOP_VERSION= for version specific")
  endif()
endif()
endif()
############



set(BUILTIN_FS_TARGETS "")
set(BUILTIN_FS_FLAGS "")
if(NOT SWC_BUILD_PKG AND SWC_BUILTIN_FS)

  if (SWC_BUILTIN_FS STREQUAL "all")
    SET (BUILTIN_FS_FLAGS "${BUILTIN_FS_FLAGS} -DBUILTIN_FS_ALL")
  else()

    string(REPLACE "," ";" SWC_BUILTIN_FS "${SWC_BUILTIN_FS}")
    list(REMOVE_DUPLICATES SWC_BUILTIN_FS)
    foreach(fs ${SWC_BUILTIN_FS})
      string(TOLOWER ${fs} fs)
      set(BUILTIN_FS_TARGETS ${BUILTIN_FS_TARGETS} swcdb_fs_${fs})
      string(TOUPPER ${fs} fs)
      set("BUILTIN_FS_${fs}" ON)
      set(BUILTIN_FS_FLAGS "${BUILTIN_FS_FLAGS} -DBUILTIN_FS_${fs}")
    endforeach()
  endif()


  # if (SWC_BUILTIN_FS STREQUAL "all" OR SWC_BUILTIN_FS STREQUAL "broker")
  #  set(BUILTIN_FS_TARGETS ${BUILTIN_FS_TARGETS} swcdb_fs_broker)
  #  if (NOT SWC_BUILTIN_FS STREQUAL "all")
  #    SET (BUILTIN_FS_FLAGS "${BUILTIN_FS_FLAGS} -DBUILTIN_FS_BROKER")
  #  endif()
  # endif()

endif()
