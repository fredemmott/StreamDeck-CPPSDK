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
  const auto expected_basename = filename.substr(0, extension_start);

#ifdef _MSC_VER
  const std::string expected = expected_basename + ".exe";
#else
  const std::string expected = expected_basename;
#endif
  const auto path = ESDUtilities::GetPluginExecutablePath();
  const auto actual_basename = ESDUtilities::GetFileName(path);
  CHECK(path, expected_basename, actual_basename);
  return test.result();
}
