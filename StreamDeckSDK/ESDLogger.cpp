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

namespace {
ESDConnectionManager* sConnectionManager = nullptr;
}// namespace

void ESDLogger::SetConnectionManager(ESDConnectionManager* conn) {
  sConnectionManager = conn;
}

void ESDLogger::LogToStreamDeckSoftware(const std::string& message) {
  if (!sConnectionManager) {
    return;
  }
  sConnectionManager->LogMessage(message);
}

void ESDLogger::LogMessage(const char* context, const std::string& msg) {
  const auto message = fmt::format(FMT_STRING("{}: {}"), context, msg);
  LogToStreamDeckSoftware(message);
#ifndef NDEBUG
  LogToSystem(message);
#endif
}

#ifdef __APPLE__
void ESDLogger::LogToSystem(const std::string& message) {
  os_log_with_type(
    OS_LOG_DEFAULT, OS_LOG_TYPE_DEFAULT, "%{public}s", message.c_str());
}
#endif
