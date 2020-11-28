/* Copyright (c) 2020-present, Fred Emmott
 *
 * This source code is licensed under the MIT-style license found in the
 * LICENSE file.
 */

#pragma once

#include <nlohmann/json.hpp>
#include <string>

class ESDConnectionManager;

/** Class representing a specific action (kind of button).
 *
 * A plugin can provide multiple actions, e.g.:
 * - 'mute on'
 * - 'mute off'
 * - 'toggle mute'
 *
 * Each of these can be represented by an `ESDAction` subclass.
 *
 * This class is intended to be used in conjunction with an `ESDPlugin`
 * subclass; your `ESDPlugin` subclass should contain minimum logic beyond
 * storing and instantiating `ESDAction` subclass instances as needed.
 *
 * If your action reflects state outside of the plugin (e.g. hardware state,
 * the current time, state in another application such as OBS), you may want
 * to use `ESDActionWithExternalState`.
 */
class ESDAction {
 public:
  ESDAction(ESDConnectionManager* esd_connection, const std::string& context);
  virtual ~ESDAction();

  virtual void DidReceiveSettings(const nlohmann::json& settings);
  virtual void KeyUp(const nlohmann::json& settings);
  virtual void SendToPlugin(const nlohmann::json& payload);
  virtual void WillAppear(const nlohmann::json& settings);

 protected:
  std::string GetContext() const;
  ESDConnectionManager* GetESD() const;

 private:
  std::string mContext;
  ESDConnectionManager* mESDConnection = nullptr;
};
