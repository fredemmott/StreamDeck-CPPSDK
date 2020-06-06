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
set(
  SOURCE_URL_TYPE
  GIT_REPOSITORY CACHE STRING "StreamDeckSDK.cmake: path of source repository"
)
set(
  SOURCE_URL
  https://github.com/fredemmott/StreamDeck-CPPSDK
  CACHE STRING "StreamDeckSDK.cmake: type of source repository"
)
set(
  SOURCE_REF_TYPE
  GIT_TAG
  CACHE STRING "StreamDeckSDK.cmake: type of source repository version id"
)
set(
  SOURCE_REF
  master
  CACHE STRING "StreamDeckSDK.cmake: source repository version ID"
)
configure_file(
  StreamDeckSDK.cmake.in
  StreamDeckSDK.cmake
  @ONLY
)
install(
  FILES
  ${CMAKE_CURRENT_BINARY_DIR}/StreamDeckSDK.cmake
  DESTINATION
  ${CMAKE_INSTALL_DATADIR}
)
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
install(
  FILES
  "${ASIO_INCLUDE_DIRS}/asio.hpp"
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

add_custom_target(
  install_test
  DEPENDS
  "${CMAKE_INSTALL_FULL_LIBDIR}/${CMAKE_STATIC_LIBRARY_PREFIX}StreamDeckSDK${CMAKE_STATIC_LIBRARY_SUFFIX}"
  "${CMAKE_INSTALL_FULL_INCLUDEDIR}/StreamDeckSDK/ESDBasePlugin.h"
  "${CMAKE_INSTALL_FULL_INCLUDEDIR}/nlohmann/json.hpp"
  "${CMAKE_INSTALL_FULL_INCLUDEDIR}/websocketpp/client.hpp"
  "${CMAKE_INSTALL_FULL_INCLUDEDIR}/asio/version.hpp"
  "${CMAKE_INSTALL_FULL_INCLUDEDIR}/asio.hpp"
)
