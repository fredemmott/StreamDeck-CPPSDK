// @copyright  (c) 2020, Frederick Emmott
// This source code is licensed under the MIT-style license found in
// the LICENSE file.

#include <StreamDeckSDK/ESDUtilities.h>

#include <map>

#include "Test.h"

bool test_main() {
  const std::map<std::string, std::string> data = {
#ifdef _MSC_VER
    {"C:\\", "C:\\"},
    {"C:", "C:\\"},
    {"C:\\Foo", "C:\\"},
    {"C:\\Foo\\", "C:\\"},
    {"C:\\Foo\\Bar", "C:\\Foo"},
    {"C:\\Foo\\Bar\\Baz", "C:\\Foo\\Bar"},
    {"D:\\Foo\\Bar\\Baz", "D:\\Foo\\Bar"},
    {"D:/Foo/Bar/Baz", "D:/Foo/Bar"},
    {"C:/Foo\\Bar/Baz", "C:/Foo\\Bar"},
    {"C:\\Foo/", "C:\\"},
    {"C:\\Foo/Bar/", "C:\\Foo"},
    {"C:/", "C:/"},
    {"C:/Foo", "C:\\"},
    {"\\\\foo\\bar", "\\\\foo"},
    {"\\\\foo\\bar\\baz", "\\\\foo\\bar"},
    {"\\\\foo\\", "\\\\foo"},
    {"\\\\foo", "\\\\foo"},
    {"\\\\foo/", "\\\\foo"},
    {"\\\\foo/bar/baz", "\\\\foo/bar"},
#else
    {"/", "/"},
    {"/foo", "/"},
    {"/foo/", "/"},
    {"/foo/bar", "/foo"},
    {"/foo/bar/", "/foo"},
    {"/foo/bar/baz", "/foo/bar"},
    {"/foo/bar/baz/", "/foo/bar"},
#endif
  };
  Test test;
  for (const auto& [in, expected] : data) {
    const auto actual = ESDUtilities::GetParentDirectoryPath(in);
    CHECK(in, expected, actual);
  }
  return test.result();
}
