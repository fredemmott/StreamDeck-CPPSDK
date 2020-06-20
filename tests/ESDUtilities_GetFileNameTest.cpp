// @copyright  (c) 2020, Frederick Emmott
// This source code is licensed under the MIT-style license found in
// the LICENSE file.

#include <StreamDeckSDK/ESDUtilities.h>

#include <map>

#include "Test.h"

bool test_main() {
  const std::map<std::string, std::string> data = {
#ifdef _MSC_VER
    {"C:", "C:\\"},
    {"C:\\", "C:\\"},
    {"C:\\Foo", "Foo"},
    {"C:\\Foo\\", "Foo"},
    {"C:\\Foo\\Bar", "Bar"},
    {"C:\\Foo\\Bar\\", "Bar"},
    {"C:\\Foo\\Bar.exe", "Bar.exe"},
    {"C:/Foo/Bar/", "Bar"},
    {"C:/Foo/Bar", "Bar"},
    {"C:/Foo/Bar.exe", "Bar.exe"},
    {"C:\\Foo/Bar.exe", "Bar.exe"},
    {"\\\\foo", "\\\\foo"},
    {"\\\\foo\\bar", "bar"},
    {"\\\\foo\\bar\\baz", "baz"},
#else
    {"/", "/"},
    {"/foo", "/foo"},
    {"/foo/", "/foo"},
    {"/foo/bar", "/foo/bar"},
    {"/foo/bar/", "/foo/bar"},
    {"/foo/bar.so", "/foo/bar.so"},
#endif
  };
  Test test;
  for (const auto& [in, expected] : data) {
    const auto actual = ESDUtilities::GetFileName(in);
    CHECK(in, expected, actual);
  }
  return test.result();
}
