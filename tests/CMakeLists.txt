add_library(
  ESDUtilititesPathTestImpl
  ESDUtilititesPathTest.cpp
)
set_target_properties(
  ESDUtilititesPathTestImpl
  PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF
)
target_link_libraries(ESDUtilititesPathTestImpl PRIVATE StreamDeckSDK)

add_executable(
	ESDUtilititesPathTest
	main.cpp
)
target_link_libraries(ESDUtilititesPathTest ESDUtilititesPathTestImpl)

add_test(NAME ESDUtilititesPathTest COMMAND ESDUtilititesPathTest)
