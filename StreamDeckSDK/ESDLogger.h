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
  static void SetConnectionManager(ESDConnectionManager* conn);

  static void LogMessage(const std::string& context, const std::string& message);
#ifdef _MSC_VER
  static void LogMessage(const char* context, const std::wstring& message);
#endif

 private:
  static void LogToStreamDeckSoftware(const std::string& message);
  static void LogToSystem(const std::string& message);
#ifdef _MSC_VER
  static void LogToSystem(const std::wstring& message);
#endif
};

#define ESDLogf(format_string, ...) ESDLogger::LogMessage(__FILE__, fmt::sprintf(format_string, __VA_ARGS__))

// The lambda + explicit 'else' block are needed to make VS2019 happy
#define _ESDLogger_format(str, ...) \
  ( \
    [=]() -> decltype(fmt::format(str)) { \
      if constexpr (std::tuple_size<decltype(std::make_tuple(__VA_ARGS__))>::value == 0) { \
        return str; \
      } else { \
        return fmt::format(FMT_STRING(str), __VA_ARGS__); \
      } \
    }() \
  )

// Not currently possible to handle empty __VA_ARGS__ portably;
// - MSVC: just works
// - GCC/Clang: if `##` is prepended, omit the `,` if needed
// - C++20: __VA_OPT__(,) __VA_ARGS__ -  not yet widely supported.
#ifdef _MSC_VER
#define ESDLog(str, ...) \
  ESDLogger::LogMessage(__FILE__, _ESDLogger_format(str, __VA_ARGS__))
#else
#define ESDLog(str, ...) \
  ESDLogger::LogMessage(__FILE__, _ESDLogger_format(str, ##__VA_ARGS__))
#endif

#ifndef NDEBUG
#define ESDDebug ESDLog
#define ESDDebugf ESDLogf
#else
#define ESDDebug(...) while (0)
#define ESDDebugf(...) while (0)
#endif
