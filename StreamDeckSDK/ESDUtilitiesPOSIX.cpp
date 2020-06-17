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

#include <unistd.h>
#include <fmt/format.h>

void ESDUtilities::DoSleep(int inMilliseconds) {
  usleep(1000 * inMilliseconds);
}

static char GetFileSystemPathDelimiter() {
  return '/';
}

std::string ESDUtilities::AddPathComponent(
  const std::string& inPath,
  const std::string& inComponentToAdd) {
  if (inPath.size() <= 0)
    return inComponentToAdd;

  char delimiter = GetFileSystemPathDelimiter();
  char lastChar = inPath[inPath.size() - 1];

  bool pathEndsWithDelimiter = (delimiter == lastChar) || ('/' == lastChar);
  bool compStartsWithDelimiter
    = (delimiter == inComponentToAdd[0]) || ('/' == inComponentToAdd[0]);

  std::string result;
  if (pathEndsWithDelimiter && compStartsWithDelimiter)
    result = inPath + inComponentToAdd.substr(1);
  else if (pathEndsWithDelimiter || compStartsWithDelimiter)
    result = inPath + inComponentToAdd;
  else
    result = inPath + GetFileSystemPathDelimiter() + inComponentToAdd;

  return result;
}

std::string ESDUtilities::GetParentDirectoryPath(const std::string& inPath) {
  const char delimiter = GetFileSystemPathDelimiter();
  const auto first_delim = inPath.find_first_of(delimiter);

  auto idx = inPath.find_last_not_of(delimiter);
  if (idx == std::string::npos) {
    return inPath;
  }
  const auto trimmed(inPath.substr(0, idx + 1));

  idx = trimmed.find_last_of(delimiter);
  if (idx == first_delim) {
    return inPath;
  }
  return trimmed.substr(0, idx);
}

std::string ESDUtilities::GetFileName(const std::string& inPath) {
  //
  // Use the platform specific delimiter
  //
  auto delimiter = GetFileSystemPathDelimiter();

  //
  // Remove the trailing delimiters
  //
  const auto lastNonDelim = inPath.find_last_not_of(delimiter);
  if (lastNonDelim == std::string::npos) {
    return std::string();
  }

  const auto normalized = inPath.substr(0, lastNonDelim + 1);

  const auto delimIdx = inPath.find_last_of(delimiter);
  if (delimIdx == std::string::npos) {
    return normalized;
  }

  return normalized.substr(delimIdx + 1);
}

std::string ESDUtilities::GetPluginDirectoryPath() {

  static std::string dir;
  if (dir.empty()) {
    const std::string executable(GetPluginExecutablePath());
    const auto search = fmt::format(".sdPlugin{}", GetFileSystemPathDelimiter());
    const auto idx = executable.rfind(search);
    dir = executable.substr(0, idx + search.size() - 1);
  }
  return dir;
}
