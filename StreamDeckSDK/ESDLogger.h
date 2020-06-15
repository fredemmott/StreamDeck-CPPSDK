// @copyright  (c) 2020, Frederick Emmott
// This source code is licensed under the MIT-style license found in
// the LICENSE file.
#pragma once

#include <fmt/format.h>
#include <fmt/printf.h>

#include <string>

class ESDConnectionManager;

class ESDLogger {
 public:
  static ESDLogger* Get();

  void SetWin32DebugPrefix(const std::string& mPrefix);
  void SetConnectionManager(ESDConnectionManager* conn);

  template <typename Tfmt, typename... Targs>
  void LogMessagef(const char* context, Tfmt fmt, Targs... args) {
    LogMessage(context, fmt::sprintf(fmt, args...));
  }

  template <typename Tfmt, typename... Targs>
  void LogMessagefmt(const char* context, Tfmt fmt, Targs... args) {
    LogMessage(context, fmt::format(fmt, args...));
  }

 private:
  ESDLogger();

  void LogMessage(const char* context, const std::string& message);
  void LogToSystem(const std::string& message);
  void LogToStreamDeckSoftware(const std::string& message);

  std::string mPrefix;
  std::wstring mWidePrefix;
  ESDConnectionManager* mConnectionManager = nullptr;

#ifdef _MSC_VER
  void LogMessage(const char* context, const std::wstring& message);
  void LogToSystem(const std::wstring& message);
#endif
};

#define ESDLogf(...) ESDLogger::Get()->LogMessagef(__FILE__, __VA_ARGS__)
#define ESDLogfmt(fmt, ...) \
  ESDLogger::Get()->LogMessagefmt(__FILE__, FMT_STRING(fmt), __VA_ARGS__)
#define ESDLog(...) ESDLogger::Get()->LogMessagef(__FILE__, __VA_ARGS__)

#ifndef NDEBUG
#define ESDDebug(...) ESDLog(__VA_ARGS__)
#define ESDDebugf(...) ESDLogf(__VA_ARGS__)
#define ESDDebugfmt(...) ESDLogfmt(__VA_ARGS__)
#else
#define ESDDebug(...) while (0)
#define ESDDebugf(...) while (0)
#define ESDDebugfmt(...) while (0)
#endif
