// @copyright  (c) 2020, Frederick Emmott
// This source code is licensed under the MIT-style license found in
// the LICENSE file.

#include <StreamDeckSDK/ESDUtilities.h>

#include "Test.h"

bool test_main() {
  Test test;

  const std::string source = __FILE__;
  const auto filename_start = source.find_last_of("/\\");
  const auto filename = source.substr(filename_start + 1);
  const auto extension_start = filename.find_last_of('.');
  const auto expected_noext = filename.substr(0, extension_start);

#ifdef _MSC_VER
  const std::string expected_filename = expected_noext + ".exe";
#else
  const std::string expected_filename = expected_noext;
#endif
  const auto path = ESDUtilities::GetPluginExecutablePath();
  const auto actual_filename = ESDUtilities::GetFileName(path);
  CHECK(path, expected_filename, actual_filename);
  return test.result();
}
