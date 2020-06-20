// @copyright  (c) 2018, Corsair Memory, Inc.
//      This source code is licensed under the MIT-style license found in the
// LICENSE file.

#include "ESDUtilities.h"

#include <unistd.h>
#include <cassert>

std::string ESDUtilities::GetPluginExecutablePath() {
  char buf[1024];
  const auto res = ::readlink("/proc/self/exe", buf, sizeof(buf));
  assert(res > 0);
  return buf;
}
