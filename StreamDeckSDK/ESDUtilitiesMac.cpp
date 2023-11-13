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
#include <cassert>

ESD::filesystem::path ESDUtilities::GetPluginExecutablePath() {
  static ESD::filesystem::path sPath;
  if (!sPath.empty()) {
    return sPath;
  }

  uint32_t bufsize = 0;
  _NSGetExecutablePath(nullptr, &bufsize);
  char buf[bufsize];
  const auto result = _NSGetExecutablePath(buf, &bufsize);
  assert(result == 0);
  sPath = { std::string_view { buf } };
  return sPath;
}
