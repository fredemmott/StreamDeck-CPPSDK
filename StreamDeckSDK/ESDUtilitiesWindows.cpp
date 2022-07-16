//==============================================================================
/**
@file       ESDUtilities.cpp

@brief      Various filesystem and other utility functions

@copyright  (c) 2018, Corsair Memory, Inc.
      This source code is licensed under the MIT-style license found in the
LICENSE file.

**/
//==============================================================================

#include <cassert>

#include "ESDLogger.h"
#include "ESDUtilities.h"
#include "windows.h"

namespace {
const char sPreferredDelimiter = '\\';
const char sValidDelimiters[] = {sPreferredDelimiter, '/', NULL};

// TODO(C++20): replace with std::string::starts_with
bool HasPrefix(const std::string& inString, const std::string& inPrefix) {
  return (inString.length() >= inPrefix.length()) && (inPrefix.length() > 0)
         && (inString.compare(0, inPrefix.length(), inPrefix) == 0);
}

// TODO(C++20): replace with std::string::ends_with
bool HasSuffix(const std::string& inString, const std::string& inSuffix) {
  return (inString.length() >= inSuffix.length()) && (inSuffix.length() > 0)
         && (inString.compare(inString.size() - inSuffix.size(), inSuffix.size(), inSuffix) == 0);
}

// Remove trailing filesystem delimiters
std::string TrimRight(const std::string& inString) {
  const auto idx = inString.find_last_not_of(sValidDelimiters);
  if (idx == std::string::npos) {
    return std::string();
  }
  return inString.substr(0, idx + 1);
}

bool IsNetworkDriveRoot(const std::string& inUtf8Path) {
  if (inUtf8Path.empty()) {
    return false;
  }
  const std::string networkPrefix = "\\\\";
  if (!HasPrefix(inUtf8Path, networkPrefix)) {
    return false;
  }
  std::string pathWithoutNetworkPrefix = inUtf8Path.substr(
    networkPrefix.length(), inUtf8Path.length() - networkPrefix.length());
  const auto pos = pathWithoutNetworkPrefix.find_first_of(sValidDelimiters);
  if (
    pos == std::string::npos || pos == pathWithoutNetworkPrefix.length() - 1) {
    return true;
  }

  return false;
}

std::string GetExtension(const std::string& inPath) {
  const std::string fileName = ESDUtilities::GetFileName(inPath);
  size_t pos = fileName.find_last_of('.');
  if (std::string::npos != pos && ((pos + 1) != fileName.length())) {
    return fileName.substr(pos);
  } else {
    return "";
  }
}

}// namespace

void ESDUtilities::DoSleep(int inMilliseconds) {
  Sleep(inMilliseconds);
}

std::string ESDUtilities::GetFileName(const std::string& inPath) {
  // Re-use the same code for special casing
  const auto parent = GetParentDirectoryPath(inPath);
  if (parent.length() >= inPath.length()) {
    return parent;
  }

  const auto trimmed = TrimRight(inPath);
  const auto pos = trimmed.find_last_of(sValidDelimiters);
  return trimmed.substr(pos + 1);
}

std::string ESDUtilities::AddPathComponent(
  const std::string& inPath,
  const std::string& inComponentToAdd) {
  if (inPath.size() <= 0)
    return inComponentToAdd;

  char delimiter = sPreferredDelimiter;
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
    result = inPath + std::string(1, sPreferredDelimiter) + inComponentToAdd;

  for (std::string::size_type i = 0; i < result.size(); i++) {
    if (result[i] == '/')
      result[i] = delimiter;
  }

  return result;
}

std::string ESDUtilities::GetParentDirectoryPath(const std::string& inPath) {
  if (HasSuffix(inPath, ":\\") || HasSuffix(inPath, ":/")) {
    return inPath;
  }

  const std::string trimmed = TrimRight(inPath);
  if (IsNetworkDriveRoot(inPath)) {
    return trimmed;
  }

  const auto pos = trimmed.find_last_of(sValidDelimiters);
  if (pos == std::string::npos) {
    if (HasSuffix(trimmed, ":"))
      return trimmed + sPreferredDelimiter;
    return std::string();
  }

  const std::string parent = inPath.substr(0, pos);

  if (HasSuffix(parent, ":\\") || HasSuffix(parent, ":/")) {
    return parent;
  }
  if (HasSuffix(parent, ":")) {
    return parent + sPreferredDelimiter;
  }

  return TrimRight(parent);
}


std::filesystem::path ESDUtilities::GetPluginExecutablePath() {
  static std::filesystem::path sPath;
  if (!sPath.empty()) {
    return sPath;
  }
  wchar_t buf[MAX_PATH];
  auto bufLen = GetModuleFileNameW(NULL, buf, MAX_PATH);
  sPath = std::wstring_view { buf, bufLen };
  return sPath;
}
