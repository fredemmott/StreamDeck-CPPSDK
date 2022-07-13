// @copyright  (c) 2020, Frederick Emmott
// This source code is licensed under the MIT-style license found in
// the LICENSE file.

#pragma once

#include <StreamDeckSDK/ESDFormat.h>

#include <iostream>
#include <string>
#include <vector>

namespace ESD {

void print(std::string_view message) {
  std::cout << message << std::flush;
}

template <class First, class... Rest>
void print(
  ESD::format_string<First, Rest...> fmt,
  First&& first,
  Rest&&... rest) {
  print(
    ESD::format(fmt, std::forward<First>(first), std::forward<Rest>(rest)...));
}

}// namespace ESD

class Test {
 public:
  bool result() {
    return mFailures.empty();
  }

  template <typename Tid, typename Tout>
  void check(const Tid& id, const Tout& expected, const Tout& actual) {
    if (expected == actual) {
      ESD::print("OK: {}\n", id);
      return;
    }
    ESD::print(
      "FAIL: {}\n  Expected:\n    {}\n  Actual:\n    {}\n", id, expected,
      actual);
    mFailures.push_back(ESD::format("{}", id));
  }

 private:
  std::vector<std::string> mFailures;
};

#define CHECK(id, expected, actual) test.check(id, expected, actual)

bool test_main();
