include(ExternalProject)

include(asio.cmake)
include(json.cmake)
include(websocketpp.cmake)

if (NOT MSVC)
  include(fmt.cmake)
endif ()
