set(
  SOURCES
  ESDAction.cpp
  ESDConnectionManager.cpp
  ESDLogger.cpp
  ESDLocalizer.cpp
  ESDMain.cpp
  ESDPlugin.cpp
)
if (WIN32)
  list(APPEND SOURCES ESDUtilitiesWindows.cpp ESDLoggerWindows)
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
target_link_libraries(
  StreamDeckSDK
  PUBLIC
  asio
  fmt
  json
  websocketpp
)
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
  target_link_libraries(StreamDeckSDK PUBLIC pthread)
endif()

file(GLOB HEADERS *.h)
set_target_properties(StreamDeckSDK PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(
  TARGETS
  StreamDeckSDK
  PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/StreamDeckSDK"
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)
