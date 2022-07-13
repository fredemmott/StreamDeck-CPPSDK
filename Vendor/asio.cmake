include(ExternalProject)

ExternalProject_Add(
  asio_source
  URL https://github.com/chriskohlhoff/asio/archive/refs/tags/asio-1-22-1.tar.gz
  URL_HASH SHA256=30cb54a5de5e465d10ec0c2026d6b5917f5e89fffabdbabeb1475846fc9a2cf0
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
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
