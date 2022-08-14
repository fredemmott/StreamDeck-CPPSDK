// @copyright  (c) 2018, Corsair Memory, Inc.
//      This source code is licensed under the MIT-style license found in the
// LICENSE file.

#include "ESDUtilities.h"

#include <unistd.h>
#include <cassert>

ESD::filesystem::path ESDUtilities::GetPluginExecutablePath() {
  static ESD::filesystem::path sPath;
  if (!sPath.empty()) {
    return sPath;
  }

  char buf[1024];
  const auto bufLen = ::readlink("/proc/self/exe", buf, sizeof(buf));
  assert(bufLen > 0);
  sPath = { std::string_view { buf, bufLen } };
  return sPath;
}
