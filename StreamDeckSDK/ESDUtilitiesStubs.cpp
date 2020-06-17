// @copyright  (c) 2018, Corsair Memory, Inc.
//      This source code is licensed under the MIT-style license found in the
// LICENSE file.

// This file contains always-failing versions of ESDUtilities, which should
// build on any platform.

#include "ESDUtilities.h"

std::string ESDUtilities::GetPluginExecutablePath() {
  abort();
}
