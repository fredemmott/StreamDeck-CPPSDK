// @copyright  (c) 2020, Frederick Emmott
// This source code is licensed under the MIT-style license found in
// the LICENSE file.

#include <StreamDeckSDK/ESDLogger.h>

#include "Test.h"

using namespace std;

bool test_main() {
  ESDLog("Hello, world");
  ESDLog("Hello, fmt {}", "world");

  #ifdef _MSC_VER
  ESDLog(L"Hello, wide world");
  ESDLog(L"Hello, wide fmt {}", L"world");
  #endif
  return true;
}
