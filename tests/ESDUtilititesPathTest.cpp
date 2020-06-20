// @copyright  (c) 2020, Frederick Emmott
// This source code is licensed under the MIT-style license found in
// the LICENSE file.

#include <StreamDeckSDK/ESDUtilities.h>
#include <fmt/format.h>

#include <iostream>
#include <map>
#include <string>

namespace {

class Test {
 public:
  bool result() {
    return mFailures.empty();
  }

  template <typename Tid, typename Tout>
  void check(const Tid& id, const Tout& expected, const Tout& actual) {
    if (expected == actual) {
      fmt::print("OK: {}\n", id);
      return;
    }
    fmt::print(
      "FAIL: {}\n  Expected:\n    {}\n  Actual:\n    {}\n", id, expected,
      actual);
    mFailures.push_back(fmt::format("{}", id));
  }

 private:
  std::vector<std::string> mFailures;
};

#define CHECK(id, expected, actual) test.check(id, expected, actual)

bool test_parent_dir() {
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
    {"C:\\Foo/", "C:\\" },
    {"C:\\Foo/Bar/", "C:\\Foo" },
    {"C:/", "C:/"},
    {"C:/Foo", "C:\\"},
    {"\\\\foo\\bar", "\\\\foo"},
    {"\\\\foo\\bar\\baz", "\\\\foo\\bar"},
    {"\\\\foo\\", "\\\\foo"},
    {"\\\\foo", "\\\\foo"},
    {"\\\\foo/", "\\\\foo"},
    {"\\\\foo/bar/baz", "\\\\foo/bar"},
#else
    {"a", "b" } // intentionally fail
#endif
  };
  Test test;
  for (const auto& [in, expected] : data) {
    const auto actual = ESDUtilities::GetParentDirectoryPath(in);
    CHECK(in, expected, actual);
  }
  return test.result();
}

}// namespace

bool test_main() {
  return test_parent_dir();
}
