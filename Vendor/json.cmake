include(ExternalProject)

ExternalProject_Add(
  json_source
  URL "https://github.com/nlohmann/json/releases/download/v3.9.1/include.zip"
  URL_HASH SHA256=6bea5877b1541d353bd77bdfbdb2696333ae5ed8f9e8cc22df657192218cad91
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
)
ExternalProject_Get_Property(json_source SOURCE_DIR)
add_library(json INTERFACE)
add_dependencies(json json_source)
target_include_directories(
 json
  INTERFACE
  "${SOURCE_DIR}/single_include"
)

install(
  DIRECTORY
  "${SOURCE_DIR}/single_include/"
  DESTINATION
  "${CMAKE_INSTALL_INCLUDEDIR}"
)
