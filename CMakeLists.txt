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

function(normalize_installdir OUTVAR INVALUE)
  get_filename_component(
    _OUTVAR
    "${INVALUE}"
    ABSOLUTE
    BASE_DIR "${CMAKE_INSTALL_PREFIX}"
  )
  set(${OUTVAR} ${_OUTVAR} PARENT_SCOPE)
endfunction()

normalize_installdir(INSTALL_ABS_LIBDIR ${CMAKE_INSTALL_LIBDIR})
normalize_installdir(INSTALL_ABS_INCLUDEDIR ${CMAKE_INSTALL_INCLUDEDIR})

add_custom_target(
  install_test
  DEPENDS
  "${INSTALL_ABS_LIBDIR}/${CMAKE_STATIC_LIBRARY_PREFIX}StreamDeckSDK${CMAKE_STATIC_LIBRARY_SUFFIX}"
  "${INSTALL_ABS_INCLUDEDIR}/StreamDeckSDK/ESDBasePlugin.h"
  "${INSTALL_ABS_INCLUDEDIR}/nlohmann/json.hpp"
  "${INSTALL_ABS_INCLUDEDIR}/websocketpp/client.hpp"
  "${INSTALL_ABS_INCLUDEDIR}/asio/version.hpp"
  "${INSTALL_ABS_INCLUDEDIR}/asio.hpp"
)
