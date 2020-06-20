// @copyright  (c) 2020, Frederick Emmott
// This source code is licensed under the MIT-style license found in
// the LICENSE file.

#pragma once

#include <fmt/format.h>

#include <vector>
#include <string>

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

bool test_main();
