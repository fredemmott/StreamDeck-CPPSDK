include(FetchContent)
include(CheckCXXSourceCompiles)

check_cxx_source_compiles("
#ifdef __APPLE__
#include <Availability.h> // for deployment target to support pre-catalina targets without std::fs
#endif
#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || (defined(__cplusplus) && __cplusplus >= 201703L)) && defined(__has_include)
#if __has_include(<filesystem>) && (!defined(__MAC_OS_X_VERSION_MIN_REQUIRED) || __MAC_OS_X_VERSION_MIN_REQUIRED >= 101500)
#define GHC_USE_STD_FS
#endif
#endif
#ifndef GHC_USE_STD_FS
#error \"std::filesystem missing or unusable\"
#endif
" HAS_STD_FILESYSTEM)

if(NOT HAS_STD_FILESYSTEM)
  FetchContent_Declare(
    filesystem
    URL https://github.com/gulrak/filesystem/archive/refs/tags/v1.5.12.zip
    URL_HASH SHA256=c11303d75ad56dca1f7273ab95cbf7e7380c4448362a4d4e63156814caf0a713
    EXCLUDE_FROM_ALL
  )

  FetchContent_MakeAvailable(filesystem)
endif()
