// @copyright  (c) 2020, Frederick Emmott
// This source code is licensed under the MIT-style license found in
// the LICENSE file.
#pragma once

#include <string>

#include "ESDFormat.h"

class ESDConnectionManager;

class ESDLogger final {
 public:
  ESDLogger() = delete;
  static void SetConnectionManager(ESDConnectionManager* conn);

  static void LogMessage(
    const std::string& context,
    const std::string& message);
#ifdef _MSC_VER
  static void LogMessage(const std::string& context, const std::wstring& message);
#endif

 private:
  static void LogToStreamDeckSoftware(const std::string& message);
  static void LogToSystem(const std::string& message);
#ifdef _MSC_VER
  static void LogToSystem(const std::wstring& message);
#endif
};

template <class Str>
void ESDLogWithContext(const std::string& context, Str&& str) {
  ESDLogger::LogMessage(context, std::forward<Str>(str));
}

template <class First, class... Rest>
void ESDLogWithContext(
  const std::string& context,
  ESD::format_string<First, Rest...> str,
  First&& first,
  Rest&&... rest) {
  ESDLogger::LogMessage(
    context,
    ESD::format(str, std::forward<First>(first), std::forward<Rest>(rest)...));
}

#ifdef _MSC_VER
template <class First, class... Rest>
void ESDLogWithContext(
  const std::string& context,
  ESD::format_wstring<First, Rest...> str,
  First&& first,
  Rest&&... rest) {
  ESDLogger::LogMessage(
    context,
    ESD::format(str, std::forward<First>(first), std::forward<Rest>(rest)...));
}
#define ESDLog(...) ESDLogWithContext(__FILE__, __VA_ARGS__)
#else
#define ESDLog(...) ESDLogWithContext(__FILE__, ##__VA_ARGS__)
#endif

#ifndef NDEBUG
#define ESDDebug ESDLog
#else
template <class... Args>
inline void ESDDebug(Args&&...) {
}
#endif
