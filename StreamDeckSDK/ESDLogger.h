// @copyright  (c) 2020, Frederick Emmott
// This source code is licensed under the MIT-style license found in
// the LICENSE file.
#pragma once

#include <fmt/format.h>
#include <fmt/printf.h>

#include <string>

class ESDConnectionManager;

class ESDLogger final {
 public:
  ESDLogger() = delete;
  static void SetWin32DebugPrefix(const std::string& mPrefix);
  static void SetConnectionManager(ESDConnectionManager* conn);

  template <typename Tfmt, typename... Targs>
  static void LogMessagef(const char* context, Tfmt fmt, Targs... args) {
    LogMessage(context, fmt::sprintf(fmt, args...));
  }

  template <typename Tfmt, typename... Targs>
  static void LogMessagefmt(const char* context, Tfmt fmt, Targs... args) {
    LogMessage(context, fmt::format(fmt, args...));
  }

 private:
  static void LogMessage(const char* context, const std::string& message);
  static void LogToSystem(const std::string& message);
  static void LogToStreamDeckSoftware(const std::string& message);
#ifdef _MSC_VER
  static void LogMessage(const char* context, const std::wstring& message);
  static void LogToSystem(const std::wstring& message);
#endif
};

#define ESDLogf(fmt, ...) ESDLogger::LogMessagef(__FILE__, fmt, __VA_ARGS__)
#define ESDLogfmt(fmt, ...) \
  ESDLogger::LogMessagefmt(__FILE__, FMT_STRING(fmt), __VA_ARGS__)
#define ESDLog(fmt, ...) ESDLogf(fmt, __VA_ARGS__)

#ifndef NDEBUG
#define ESDDebug(fmt, ...) ESDLog(fmt, __VA_ARGS__)
#define ESDDebugf(fmt, ...) ESDLogf(fmt, __VA_ARGS__)
#define ESDDebugfmt(fmt, ...) ESDLogfmt(fmt, __VA_ARGS__)
#else
#define ESDDebug(...) while (0)
#define ESDDebugf(...) while (0)
#define ESDDebugfmt(...) while (0)
#endif
