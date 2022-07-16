//==============================================================================
/**
@file       ESDUtilities.cpp

@brief      Various filesystem and other utility functions

@copyright  (c) 2018, Corsair Memory, Inc.
      This source code is licensed under the MIT-style license found in the
LICENSE file.

**/
//==============================================================================

#include <unistd.h>

#include "ESDFormat.h"
#include "ESDLogger.h"
#include "ESDUtilities.h"

namespace {
// Remove trailing delimiters
std::string TrimRight(const std::string& in) {
  const auto idx = in.find_last_not_of('/');
  if (idx == std::string::npos) {
    return "/";
  }
  return in.substr(0, idx + 1);
}
}// namespace

void ESDUtilities::DoSleep(int inMilliseconds) {
  usleep(1000 * inMilliseconds);
}

std::string ESDUtilities::AddPathComponent(
  const std::string& inPath,
  const std::string& inComponentToAdd) {
  if (inPath.size() <= 0)
    return inComponentToAdd;

  char lastChar = inPath[inPath.size() - 1];

  bool pathEndsWithDelimiter = lastChar == '/';
  bool compStartsWithDelimiter = inComponentToAdd[0] == '/';

  std::string result;
  if (pathEndsWithDelimiter && compStartsWithDelimiter)
    result = inPath + inComponentToAdd.substr(1);
  else if (pathEndsWithDelimiter || compStartsWithDelimiter)
    result = inPath + inComponentToAdd;
  else
    result = inPath + '/' + inComponentToAdd;

  return result;
}

std::string ESDUtilities::GetParentDirectoryPath(const std::string& inPath) {
  if (inPath.empty()) {
    return "/";
  }
  if (inPath[0] != '/') {
    ESDDebug("Relative paths are not supported");
    return {};
  }

  const auto trimmed(TrimRight(inPath));

  const auto idx = trimmed.find_last_of('/');
  if (idx == 0) {
    return "/";
  }
  return trimmed.substr(0, idx);
}

std::string ESDUtilities::GetFileName(const std::string& inPath) {
    // Re-use the same code for special casing
  const auto parent = GetParentDirectoryPath(inPath);
  if (parent.length() >= inPath.length()) {
    return parent;
  }

  const auto trimmed = TrimRight(inPath);
  const auto pos = trimmed.find_last_of('/');
  return trimmed.substr(pos + 1);
}
