//==============================================================================
/**
@file       ESDUtilities.h

@brief      Various filesystem and other utility functions

@copyright  (c) 2018, Corsair Memory, Inc.
      This source code is licensed under the MIT-style license found in the
LICENSE file.

**/
//==============================================================================

#pragma once

#include <filesystem>
#include <string>

class ESDUtilities {
 public:
  // Get the path of the .sdPlugin bundle
  static std::filesystem::path GetPluginDirectoryPath();
  // Get the path of the full executable
  static std::filesystem::path GetPluginExecutablePath();

  [[deprecated("use std::this_thread::sleep_for() instead")]]
  static void DoSleep(int inMilliseconds);

  // Return a path with the appending path component
  [[deprecated("Use std::filesystem::path instead")]] static std::string
  AddPathComponent(
    const std::string &inPath,
    const std::string &inComponentToAdd);

  // Return the path without the last component (dirname). Returns path if it is
  // already a root folder (i.e. 'C:\\', '\\ABC' or '/'). Return an empty string
  // if error
  [[deprecated("Use std::filesystem::path instead")]] static std::string
  GetParentDirectoryPath(const std::string &inPath);

  // Return the last component of the path (basename)
  [[deprecated("Use std::filesystem::path instead")]] static std::string
  GetFileName(const std::string &inPath);
};
