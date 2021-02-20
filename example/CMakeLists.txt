cmake_minimum_required(VERSION 3.15)

# CMAKE_MSVC_RUNTIME_POLICY support
cmake_policy(SET CMP0091 NEW)
# Statically link the MSVC runtime
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

project(
  com.fredemmott.cppsdk.demo.sdPlugin
  VERSION 0.0.1
  LANGUAGES CXX
)

include("StreamDeckSDK.cmake")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_EXTENSIONS false)
if (MSVC)
  add_definitions("/Zc:__cplusplus -DUNICODE=1")
endif()

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(
    CMAKE_INSTALL_PREFIX
    "${STREAMDECK_PLUGIN_DIR}/${CMAKE_PROJECT_NAME}"
    CACHE PATH "..." FORCE
  )
endif()
message(STATUS "Install dir: ${CMAKE_INSTALL_PREFIX}")

add_executable(mydemoplugin main.cpp)
target_link_libraries(mydemoplugin StreamDeckSDK)
install(TARGETS mydemoplugin DESTINATION ${CMAKE_INSTALL_PREFIX})

# If doing a Debug or RelWithDebInfo build, install the debug symbols too
# On MacOS, these are part of the executable
if(WIN32)
  install(FILES "$<TARGET_PDB_FILE:mydemoplugin>" DESTINATION ${CMAKE_INSTALL_PREFIX} OPTIONAL)
endif()

install(FILES manifest.json DESTINATION ${CMAKE_INSTALL_PREFIX})
