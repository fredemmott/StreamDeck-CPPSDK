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
bool HasPrefix(
  const std::string& inString,
  const std::string& inPrefix) {
  return (inString.length() >= inPrefix.length()) && (inPrefix.length() > 0)
         && (inString.compare(0, inPrefix.length(), inPrefix) == 0);
}

// TODO(C++20): replace with std::string::ends_with
bool HasSuffix(
  const std::string& inString,
  const std::string& inSuffix) {
  return (inString.length() >= inSuffix.length()) && (inSuffix.length() > 0)
         && (inString.compare(inString.size() - inSuffix.size(), inSuffix.size(), inSuffix) == 0);
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
	size_t pos = fileName.find_last_of(".");
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
  // Use the platform specific delimiter
  //
  std::string delimiterString = std::string(1, sPreferredDelimiter);
  //
  // On Windows, check if the platform specific delimiter is used.
  // If not, fallback on the delimiter "/"
  //
  size_t delimiterPosition = inPath.find_last_of(delimiterString);
  if (std::string::npos == delimiterPosition) {
    delimiterString = "/";
    delimiterPosition = inPath.find_last_of(delimiterString);
    if (std::string::npos == delimiterPosition) {
      // No delimiter -> return the path
      return inPath;
    }
  } else {
    // Special handling "C:\\"
    if (HasSuffix(inPath, ":\\"))
      return inPath;
  }

  //
  // Remove the trailing delimiters
  //
  std::string pathWithoutTrailingDelimiter = inPath;
  while (pathWithoutTrailingDelimiter.length() > delimiterString.length()
         && HasSuffix(pathWithoutTrailingDelimiter, delimiterString)) {
    pathWithoutTrailingDelimiter = pathWithoutTrailingDelimiter.substr(
      0, pathWithoutTrailingDelimiter.length() - delimiterString.length());
  }

  //
  // Special cases
  //
  if (
    pathWithoutTrailingDelimiter.empty()
    || pathWithoutTrailingDelimiter == delimiterString) {
    return delimiterString;
  }

  //
  // Get the last path component
  //
  size_t pos = pathWithoutTrailingDelimiter.find_last_of(delimiterString);
  if (std::string::npos != pos && pathWithoutTrailingDelimiter.length() > pos) {
    return pathWithoutTrailingDelimiter.substr(pos + 1);
  }

  //
  // Fallback
  //
  return pathWithoutTrailingDelimiter;
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

  if (IsNetworkDriveRoot(inPath)) {
    // Trim trailing slashes
    const auto last = inPath.find_last_not_of(sValidDelimiters);
    if (last == std::string::npos) {
      return "";
    }
    return inPath.substr(0, last + 1);
  }

  //
  // Remove the trailing delimiters
  //
  size_t pos = inPath.find_last_not_of(sValidDelimiters);
  if (pos == std::string::npos)
    return "";
  const std::string pathWithoutTrailingDelimiters = inPath.substr(0, pos + 1);

  pos = pathWithoutTrailingDelimiters.find_last_of(sValidDelimiters);
  if (pos == std::string::npos) {
    if (HasSuffix(pathWithoutTrailingDelimiters, ":"))
      return pathWithoutTrailingDelimiters + sPreferredDelimiter;
    return "";
  }

  const std::string parent = inPath.substr(0, pos);

  if (HasSuffix(parent, ":\\") || HasSuffix(parent, ":/")) {
    return parent;
  }
  if (HasSuffix(parent, ":")) {
    return parent + sPreferredDelimiter;
  }

  // Trim trailing delimiters again
  pos = parent.find_last_not_of(sValidDelimiters);
  if (pos == std::string::npos)
    return "";
  return parent.substr(0, pos + 1);
}

std::string ESDUtilities::GetPluginDirectoryPath() {
  static std::string sPluginPath;

  if (sPluginPath.empty()) {
    std::string pathString(GetPluginExecutablePath());

    while (!pathString.empty()) {
      if (pathString == "/" || HasSuffix(pathString, ":\\")) {
        break;
      }

      std::string pathExtension = GetExtension(pathString);
      if (pathExtension == ".sdPlugin") {
        sPluginPath = pathString;
        break;
      }

      std::string parentPath = GetParentDirectoryPath(pathString);
      if (parentPath != pathString) {
        pathString = parentPath;
      } else {
        break;
      }
    }
  }

  return sPluginPath;
}

std::string ESDUtilities::GetPluginExecutablePath() {
  char* native = nullptr;
  _get_pgmptr(&native);
  assert(native);
  return native;
}
