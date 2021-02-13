include(ExternalProject)

ExternalProject_Add(
  asio_source
  URL https://github.com/chriskohlhoff/asio/archive/asio-1-18-1.tar.gz
  URL_HASH SHA512=c84e6fca448ed419a976756840f3f4543291a5a7d4f62d4de7c06945b2cd9ececca6633049ad5e36367d60f67a4f2735be017445514ae9fa9497d4af2a4d48f8
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  PATCH_COMMAND
    git init && git apply --ignore-whitespace "${CMAKE_CURRENT_LIST_DIR}/asio-7377f941cc9831c4c3cba1e71d3bc29bddf1a700.patch"
)
ExternalProject_Get_Property(asio_source SOURCE_DIR)
add_library(asio INTERFACE)
add_dependencies(asio asio_source)
target_compile_definitions(
  asio
  INTERFACE
  ASIO_STANDALONE=1
)
target_include_directories(
  asio
  INTERFACE
  ${SOURCE_DIR}/asio/include
)

install(
       DIRECTORY
  ${SOURCE_DIR}/asio/include/
       DESTINATION
  "${CMAKE_INSTALL_INCLUDEDIR}"
  FILES_MATCHING
  PATTERN "*.hpp"
  PATTERN "*.ipp"
)
