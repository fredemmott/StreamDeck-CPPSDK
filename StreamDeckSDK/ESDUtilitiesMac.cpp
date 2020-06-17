//==============================================================================
/**
@file       ESDUtilities.cpp

@brief      Various filesystem and other utility functions

@copyright  (c) 2018, Corsair Memory, Inc.
      This source code is licensed under the MIT-style license found in the
LICENSE file.

**/
//==============================================================================

#include "ESDUtilities.h"

#include <mach-o/dyld.h>

std::string ESDUtilities::GetPluginExecutablePath() {
  static std::string path;
  if (path.empty()) {
    uint32_t bufsize = 0;
    _NSGetExecutablePath(nullptr, &bufsize);
    char buf[bufsize];
    const auto success = _NSGetExecutablePath(buf, &bufsize);
    assert(success);
    path = std::string(buf);
  }
  return path;
}
