// @copyright  (c) 2020, Frederick Emmott
// This source code is licensed under the MIT-style license found in
// the LICENSE file.
#pragma once

#include <version>

#ifdef __cpp_lib_format
#include <format>
namespace ESD {
using std::format;
};
#else
#include <fmt/format.h>
namespace ESD {
using fmt::format;
};
#endif

#include <string>

class ESDConnectionManager;

class ESDLogger final {
 public:
  ESDLogger() = delete;
  static void SetConnectionManager(ESDConnectionManager* conn);

  static void LogMessage(
    const std::string& context,
    const std::string& message);
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

#define ESDLog(formatString, ...) \
  if constexpr ( \
    std::tuple_size_v<decltype(std::make_tuple(__VA_ARGS__))> == 0) { \
    ESDLogger::LogMessage(__FILE__, formatString); \
  } else { \
    ESDLogger::LogMessage(__FILE__, ESD::format(formatString, __VA_ARGS__)); \
  }

#ifdef DEBUG
#define ESDDebug ESDLog
#else
#define ESDDebug(...) while(0)
#endif
