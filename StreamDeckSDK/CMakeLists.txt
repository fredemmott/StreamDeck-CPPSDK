set(
  SOURCES
  ESDConnectionManager.cpp
  ESDLogger.cpp
  ESDLocalizer.cpp
  ESDMain.cpp
)
if (WIN32)
  list(APPEND SOURCES ESDLoggerWindows.cpp ESDUtilitiesWindows.cpp)
elseif (APPLE)
  list(APPEND SOURCES ESDUtilitiesMac.cpp)
else()
  list(APPEND SOURCES ESDUtilitiesStubs.cpp)
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

if (APPLE)
  find_library(CORE_FOUNDATION_LIBRARY CoreFoundation REQUIRED)
  target_link_libraries(
    StreamDeckSDK
    PUBLIC
    ${CORE_FOUNDATION_LIBRARY}
  )
endif()

file(GLOB HEADERS *.h)
set_target_properties(StreamDeckSDK PROPERTIES PUBLIC_HEADER "${HEADERS}")
