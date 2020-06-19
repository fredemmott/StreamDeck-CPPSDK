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
  static void LogMessage(const char* context, Tfmt fmt, Targs... args) {
    LogMessage(context, fmt::format(fmt, args...));
  }

  static void LogMessage(const char* context, const std::string& message);
#ifdef _MSC_VER
  static void LogMessage(const char* context, const std::wstring& message);
#endif

 private:
  static void LogToSystem(const std::string& message);
  static void LogToStreamDeckSoftware(const std::string& message);
#ifdef _MSC_VER
  static void LogToSystem(const std::wstring& message);
#endif
};

#define ESDLogf(...) ESDLogger::LogMessagef(__FILE__, __VA_ARGS__)

// Not currently possible to handle empty __VA_ARGS__ portably;
// - MSVC: just works
// - GCC/Clang: if `##` is prepended, omit the `,` if needed
// - C++20: __VA_OPT__(,) __VA_ARGS__ -  not yet widely supported.
#ifdef _MSC_VER
#define ESDLog(fmt, ...) \
  ESDLogger::LogMessage(__FILE__, FMT_STRING(fmt), __VA_ARGS__)
#else
#define ESDLog(fmt, ...) \
  ESDLogger::LogMessage(__FILE__, FMT_STRING(fmt), ##__VA_ARGS__)
#endif

#ifndef NDEBUG
#define ESDDebug ESDLog
#define ESDDebugf ESDLogf
#else
#define ESDDebug(...) while (0)
#define ESDDebugf(...) while (0)
#endif
