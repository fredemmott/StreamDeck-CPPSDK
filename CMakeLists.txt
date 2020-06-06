cmake_minimum_required(VERSION 3.10)

project(com.fredemmott.streamdeckcppsdk VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED true)
if (MSVC)
  add_definitions("/Zc:__cplusplus")
endif()
include_directories("${CMAKE_SOURCE_DIR}")

add_subdirectory(Vendor)
add_subdirectory(StreamDeckSDK)

include(GnuInstallDirs)
install(
  TARGETS
  StreamDeckSDK
  PUBLIC_HEADER
  DESTINATION
  "${CMAKE_INSTALL_INCLUDEDIR}/StreamDeckSDK"
)
get_target_property(
  ASIO_INCLUDE_DIRS
  asio
  INTERFACE_INCLUDE_DIRECTORIES
)
install(
  DIRECTORY
  "${ASIO_INCLUDE_DIRS}/asio"
  DESTINATION
  "${CMAKE_INSTALL_INCLUDEDIR}"
)
get_target_property(
  JSON_INCLUDE_DIRS
  json 
  INTERFACE_INCLUDE_DIRECTORIES
)
install(
  DIRECTORY
  "${JSON_INCLUDE_DIRS}/nlohmann"
  DESTINATION
  "${CMAKE_INSTALL_INCLUDEDIR}"
)
get_target_property(
  WEBSOCKETPP_INCLUDE_DIRS
  websocketpp
  INTERFACE_INCLUDE_DIRECTORIES
)
install(
  DIRECTORY
  "${WEBSOCKETPP_INCLUDE_DIRS}/websocketpp"
  DESTINATION
  "${CMAKE_INSTALL_INCLUDEDIR}"
)
