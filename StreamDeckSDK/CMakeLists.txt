set(
  SOURCES
  ESDAction.cpp
  ESDConnectionManager.cpp
  ESDFilesystem.cpp
  ESDUtilities.cpp
  ESDLogger.cpp
  ESDLocalizer.cpp
  ESDMain.cpp
  ESDPlugin.cpp
)
if (WIN32)
  list(APPEND SOURCES ESDUtilitiesWindows.cpp ESDLoggerWindows.cpp)
elseif (APPLE)
  list(APPEND SOURCES ESDUtilitiesPOSIX.cpp ESDUtilitiesMac.cpp)
else()
  list(APPEND SOURCES ESDUtilitiesPOSIX.cpp ESDUtilitiesLinux.cpp)
endif()

add_library(
  StreamDeckSDK
  STATIC
  ${SOURCES}
)
target_compile_definitions(StreamDeckSDK PRIVATE JSON_USE_IMPLICIT_CONVERSIONS=0)
target_link_libraries(
  StreamDeckSDK
  PUBLIC
  asio
  json
  websocketpp
)
if (HAS_STD_FILESYSTEM)
  target_compile_definitions(StreamDeckSDK PUBLIC ESD_HAS_STD_FILESYSTEM)
else()
  target_link_libraries(StreamDeckSDK PUBLIC ghc_filesystem)
endif()
if (NOT MSVC)
  target_link_libraries(StreamDeckSDK PUBLIC fmt)
endif()
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
  target_link_libraries(StreamDeckSDK PUBLIC pthread)
endif()

file(GLOB HEADERS *.h)
set_target_properties(
  StreamDeckSDK
  PROPERTIES
  PUBLIC_HEADER "${HEADERS}"
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF
)
target_include_directories(StreamDeckSDK PUBLIC "${CMAKE_CURRENT_LIST_DIR}/..")

install(
  TARGETS
  StreamDeckSDK
  PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/StreamDeckSDK"
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)
