// @copyright  (c) 2018, Corsair Memory, Inc.
// @copyright  (c) 2020, Frederick Emmott
// This source code is licensed under the MIT-style license found in
// the LICENSE file.

#include <Windows.h>

#include <map>
#include <string>

#include "ESDLogger.h"

namespace {
std::string sPrefix;
std::wstring sWidePrefix;
std::map<std::string, std::wstring> sWideContexts;

std::wstring MakeWideString(const std::string& str) {
  const int wlen = MultiByteToWideChar(
    CP_UTF8, NULL, str.data(), (int)str.size(), NULL, NULL);
  std::wstring wstr(wlen, 0);
  MultiByteToWideChar(
    CP_UTF8, NULL, str.data(), (int)str.size(), &wstr[0], wlen);
  return wstr;
}

std::wstring GetWideContext(const char* context) {
  auto it = sWideContexts.find(context);
  if (it != sWideContexts.end()) {
    return it->second;
  }
  auto wstr = MakeWideString(context);
  sWideContexts[context] = wstr;
  return wstr;
}
}// namespace

void ESDLogger::SetWin32DebugPrefix(const std::string& prefix) {
  sPrefix = prefix;
  sWidePrefix = MakeWideString(prefix);
}

void ESDLogger::LogMessage(const char* context, const std::wstring& wmsg) {
  const auto wbuf
    = fmt::format(FMT_STRING(L"{}: {}"), GetWideContext(context), wmsg);
#ifndef NDEBUG
  LogToSystem(wbuf);
#endif

  const auto len = WideCharToMultiByte(
    CP_UTF8, NULL, &wbuf[0], (int)wbuf.size(), nullptr, -1, 0, 0);
  std::string buf(len, 0);
  WideCharToMultiByte(
    CP_UTF8, NULL, &wbuf[0], (int)wbuf.size(), &buf[0], len, 0, 0);
  LogToStreamDeckSoftware(buf);
}

void ESDLogger::LogToSystem(const std::string& message) {
  const auto buf = sPrefix + message;
  OutputDebugStringA(buf.c_str());
}

void ESDLogger::LogToSystem(const std::wstring& message) {
  const auto buf = sWidePrefix + message;
  OutputDebugStringW(buf.c_str());
}
