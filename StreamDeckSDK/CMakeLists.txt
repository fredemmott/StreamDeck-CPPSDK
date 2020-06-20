set(
  SOURCES
  ESDConnectionManager.cpp
  ESDLogger.cpp
  ESDLocalizer.cpp
  ESDMain.cpp
)
if (WIN32)
  list(APPEND SOURCES ESDUtilitiesWindows.cpp)
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

file(GLOB HEADERS *.h)
set_target_properties(StreamDeckSDK PROPERTIES PUBLIC_HEADER "${HEADERS}")
