// @copyright  (c) 2018, Corsair Memory, Inc.
//      This source code is licensed under the MIT-style license found in the
// LICENSE file.

// This file contains always-failing versions of ESDUtilities, which should
// build on any platform.

#include "ESDUtilities.h"

void ESDUtilities::DoSleep(int inMilliseconds) {
  abort();
}

std::string ESDUtilities::AddPathComponent(
  const std::string& inPath,
  const std::string& inComponentToAdd) {
  abort();
}

std::string ESDUtilities::GetFolderPath(const std::string& inPath) {
  abort();
}

std::string ESDUtilities::GetFileName(const std::string& inPath) {
  abort();
}

std::string ESDUtilities::GetPluginPath() {
  abort();
}
