#
# Copyright (C) 2019 SWC-DB (author: Kashirin Alex (kashirin.alex@gmail.com))
#




SET_DEPS(NAME "EXPAT" REQUIRED TRUE LIB_PATHS "" INC_PATHS "" STATIC libexpat.a SHARED expat INCLUDE expat.h)
# INSTALL_LIBS(lib ${EXPAT_LIBRARIES_SHARED})

SET_DEPS(NAME "ZLIB"  REQUIRED TRUE LIB_PATHS "" INC_PATHS "" STATIC libz.a SHARED z INCLUDE zlib.h)
#INSTALL_LIBS(lib ${ZLIB_LIBRARIES_SHARED})

SET_DEPS(NAME "BZIP2" REQUIRED TRUE LIB_PATHS "" INC_PATHS "" STATIC libbz2.a SHARED bz2 INCLUDE bzlib.h)
#INSTALL_LIBS(lib ${BZIP2_LIBRARIES_SHARED})

SET_DEPS(NAME "LZMA"  REQUIRED TRUE LIB_PATHS "" INC_PATHS "" STATIC liblzma.a SHARED lzma INCLUDE lzma.h)
#INSTALL_LIBS(lib ${LZMA_LIBRARIES_SHARED})

SET_DEPS(NAME "ZSTD"  REQUIRED TRUE LIB_PATHS "" INC_PATHS "" STATIC libzstd.a SHARED zstd INCLUDE zstd.h)
#INSTALL_LIBS(lib ${ZSTD_LIBRARIES_SHARED})

SET_DEPS(NAME "SNAPPY" REQUIRED TRUE LIB_PATHS "" INC_PATHS "" STATIC libsnappy.a SHARED snappy INCLUDE snappy.h)
#INSTALL_LIBS(lib ${SNAPPY_LIBRARIES_SHARED})


SET_DEPS(NAME "RE2" REQUIRED TRUE LIB_PATHS "" INC_PATHS "" STATIC libre2.a SHARED re2 INCLUDE re2/re2.h)
#INSTALL_LIBS(lib ${RE2_LIBRARIES_SHARED})


# find_package(Doxygen)

# SET_DEPS(NAME "EVENT" REQUIRED TRUE LIB_PATHS "" INC_PATHS "" STATIC libevent.a SHARED event INCLUDE event.h)
# INSTALL_LIBS(lib  ${EVENT_LIBRARIES_SHARED})
# find_package(Thrift REQUIRED)


# find_package(Editline REQUIRED)

# find_package(Libssl REQUIRED)

# find_package(Libssh REQUIRED)



# find_package(Cronolog REQUIRED)
# find_package(RRDtool REQUIRED)
