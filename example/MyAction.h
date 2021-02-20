#pragma once

#include <StreamDeckSDK/ESDAction.h>
#include <StreamDeckSDK/ESDLogger.h>

class MyAction final : public ESDAction {
  using ESDAction::ESDAction;

  virtual void KeyDown(const nlohmann::json& settings) override {
    ESDLog("KeyDown");
  }

  virtual void KeyUp(const nlohmann::json& settings) override {
    // Log in release and debug builds
    ESDLog("KeyUp");
    ShowOK();
    // Only log in debug builds (C++20-style format strings):
    ESDDebug("Settings: {}", settings.dump());
    // ... or with sprintf-style:
    // Need to store the std::string as otherwise the c_str() of temporary
    // is invalid
    const auto buf = settings.dump();
    ESDDebugf("Settings: %s", buf.c_str());
  }

  virtual void WillAppear(const nlohmann::json& settings) override {
    ESDLog("WillAppear");
  }

  virtual void SendToPlugin(const nlohmann::json& message) override {
    ESDLog("Received message from property inspector: {}", message.dump());
  }
};
