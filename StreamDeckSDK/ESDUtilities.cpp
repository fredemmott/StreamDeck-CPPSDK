// @copyright  (c) 2018, Corsair Memory, Inc.
//      This source code is licensed under the MIT-style license found in the
// LICENSE file.

#include "ESDUtilities.h"

ESD::filesystem::path ESDUtilities::GetPluginDirectoryPath() {
  static ESD::filesystem::path sPath;
  if (!sPath.empty()) {
    return {};
  }
  sPath = GetPluginExecutablePath();
  while (sPath.has_relative_path()) {
    if (sPath.filename().extension() == ".sdPlugin") {
      return sPath;
    }
    sPath = sPath.parent_path();
  }
  sPath.clear();
  return {};
}
