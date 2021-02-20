#pragma once

#include "MyAction.h"

#include <StreamDeckSDK/ESDPlugin.h>
#include <StreamDeckSDK/ESDLogger.h>

class MyPlugin final : public ESDPlugin  {
  public:
    using ESDPlugin::ESDPlugin;

    virtual std::shared_ptr<ESDAction> GetOrCreateAction(
      const std::string& action,
      const std::string& context
    ) override {
      auto it = mActions.find(context);
      if (it != mActions.end()) {
        return it->second;
      }

      if (action == "com.fredemmott.cppsdk.demo.myaction") {
        auto impl = std::make_shared<MyAction>(
          mConnectionManager,
          action,
          context
        );
        mActions.emplace(context, impl);
        return impl;
      }

      ESDLog("Asked to get or create unknown action: {}", action);
      return nullptr;
    }

    // Overriding from ESDBasePlugin
    virtual void DidReceiveGlobalSettings(
      const nlohmann::json& payload
    ) override {
      ESDLog("Received global settings");
      ESDDebug("Global settings: {}", payload.dump());

      // Do plugin-wide stuff here, e.g. reconnect to application being
      // controlled

      for (const auto& action: mActions) {
        // ... then pass it on to each action, e.g.:
        // action->setApplicationConnection(myConnectionObject);
      }
    }
  private:
    std::map<std::string, std::shared_ptr<MyAction>> mActions;
};
