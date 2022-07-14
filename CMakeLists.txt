cmake_minimum_required(VERSION 3.21)

project(com.fredemmott.streamdeckcppsdk VERSION 2.0.1 LANGUAGES CXX)

if (PROJECT_IS_TOP_LEVEL)
  set(CMAKE_XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH NO)
  if (MSVC)
    add_compile_options(
      "/diagnostics:caret"
    )
  endif()
endif()

include(GNUInstallDirs)
add_subdirectory(Vendor)
add_subdirectory(StreamDeckSDK)

option(BUILD_LIB_ONLY "Only build the library, not tests etc" OFF)

if(NOT BUILD_LIB_ONLY)
    include(CTest)
    add_subdirectory(tests)
endif()

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
  CACHE STRING "StreamDeckSDK.cmake: source repository version ID"
)
configure_file(
  StreamDeckSDK.cmake.in
  StreamDeckSDK.cmake
  @ONLY
)

if(NOT BUILD_LIB_ONLY)
  set(SOURCE_URL_TYPE SOURCE_DIR)
  set(SOURCE_URL "\${CMAKE_CURRENT_SOURCE_DIR}/../")
  configure_file(
    StreamDeckSDK.cmake.in
    ${CMAKE_CURRENT_LIST_DIR}/example/StreamDeckSDK.cmake
    @ONLY
    NEWLINE_STYLE UNIX
  )
endif()

install(
  FILES
  ${CMAKE_CURRENT_BINARY_DIR}/StreamDeckSDK.cmake
  ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE
  DESTINATION
  ${CMAKE_INSTALL_DATADIR}
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
