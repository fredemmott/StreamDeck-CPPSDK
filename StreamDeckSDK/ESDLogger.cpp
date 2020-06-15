// @copyright  (c) 2018, Corsair Memory, Inc.
// @copyright  (c) 2020, Frederick Emmott
// This source code is licensed under the MIT-style license found in
// the LICENSE file.

#include "ESDLogger.h"

#include "ESDConnectionManager.h"
#include "ESDUtilities.h"

#ifdef __APPLE__
#include <os/log.h>
#endif
#ifdef _MSC_VER
#include <Windows.h>
#include <strsafe.h>
#else
#include <cstdarg>
#include <cstdio>
#endif

namespace {
ESDLogger* sLogger = nullptr;
}

ESDLogger* ESDLogger::Get() {
  if (!sLogger) {
    sLogger = new ESDLogger();
  }
  return sLogger;
}

ESDLogger::ESDLogger() {
}

void ESDLogger::SetWin32DebugPrefix(const std::string& prefix) {
  mPrefix = prefix;
#ifdef _MSC_VER
  const int wlen = MultiByteToWideChar(CP_UTF8, NULL, prefix.data(), prefix.size(), NULL, NULL);
  std::wstring wstr(wlen, 0);
  MultiByteToWideChar(CP_UTF8, NULL, prefix.data(), prefix.size(), &wstr[0], wlen);
  mWidePrefix = wstr;
#endif
}

void ESDLogger::SetConnectionManager(ESDConnectionManager* conn) {
  mConnectionManager = conn;
}

void ESDLogger::LogToStreamDeckSoftware(const std::string& message) {
  if (!mConnectionManager) {
    return;
  }
  mConnectionManager->LogMessage(message);
}

void ESDLogger::LogMessage(
  const char* file,
  const std::string& msg
) {
  const auto message = fmt::format(FMT_STRING("{}: {}"), file, msg);
  this->LogToStreamDeckSoftware(message);
#ifndef NDEBUG
  this->LogToSystem(message);
#endif
}

#ifdef _MSC_VER
void ESDLogger::LogMessage(
  const char* file,
  const std::wstring& wmsg
) {
  const auto wlen = MultiByteToWideChar(CP_UTF8, NULL, file, -1, NULL, NULL);
  std::wstring wfile(wlen, 0);
  MultiByteToWideChar(CP_UTF8, NULL, file, -1, &wfile[0], wlen);
  wfile.resize(wlen - 1);

  const auto wbuf = fmt::format(FMT_STRING(L"{}: {}"), wfile, wmsg);
#ifndef NDEBUG
  this->LogToSystem(wbuf);
#endif

  const auto len = WideCharToMultiByte(CP_UTF8, NULL, &wbuf[0], wbuf.size(), nullptr, -1, 0, 0);
  std::string buf(len, 0);
  WideCharToMultiByte(CP_UTF8, NULL, &wbuf[0], wbuf.size(), &buf[0], len, 0, 0);
  this->LogToStreamDeckSoftware(buf);
}
#endif

void ESDLogger::LogToSystem(const std::string& message) {
#ifdef __APPLE__
  os_log_with_type(
    OS_LOG_DEFAULT, OS_LOG_TYPE_DEFAULT, "%{public}s", message.c_str());
#endif
#ifdef _MSC_VER
  const auto buf = mPrefix + message;
  OutputDebugStringA(buf.c_str());
#endif
}

#ifdef _MSC_VER
void ESDLogger::LogToSystem(const std::wstring& message) {
  const auto buf = mWidePrefix + message;
  OutputDebugStringW(buf.c_str());
}
#endif
