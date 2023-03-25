include(FetchContent)
include(CheckCXXSourceCompiles)

if(MSVC)
  set(CMAKE_REQUIRED_FLAGS "/std:c++20 /Zc:__cplusplus")
endif()

# MacOS < 10.15 has `<filesystem>` but not `std::filesystem::path`
check_cxx_source_compiles("
#include <filesystem>

int main() {
  std::filesystem::path path;
  return 0;
}
" HAS_STD_FILESYSTEM_PATH)

if(NOT HAS_STD_FILESYSTEM_PATH)
  if(WIN32)
    message(FATAL_ERROR "Refusing to use `ghc::filesystem` on Windows due to differing locale behavior")
  endif()
  FetchContent_Declare(
    filesystem
    URL https://github.com/gulrak/filesystem/archive/refs/tags/v1.5.12.zip
    URL_HASH SHA256=c11303d75ad56dca1f7273ab95cbf7e7380c4448362a4d4e63156814caf0a713
    EXCLUDE_FROM_ALL
  )

  FetchContent_MakeAvailable(filesystem)
endif()
