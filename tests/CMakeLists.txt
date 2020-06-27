file(GLOB TESTS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*Test.cpp")
foreach(TEST_SOURCE ${TESTS})
  string(REPLACE ".cpp" "" TEST "${TEST_SOURCE}")
  # Build as a shared library so that we can test that
  # ESDUtilities::GetPluginExecutablePath() returns the executable name,
  # not the shared object/DLL name
  add_library("${TEST}Impl" "${TEST_SOURCE}")
  target_link_libraries("${TEST}Impl" PRIVATE StreamDeckSDK fmt)
  add_executable("${TEST}" main.cpp)
  target_link_libraries("${TEST}" "${TEST}Impl")

  set_target_properties(
    "${TEST}Impl"
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
  )
  add_test(
    NAME "${TEST}" COMMAND "${TEST}"
  )
endforeach()
