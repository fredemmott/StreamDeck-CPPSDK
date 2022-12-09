/* Copyright (c) 2020-present, Fred Emmott
 *
 * This source code is licensed under the MIT-style license found in the
 * LICENSE file.
 */

#pragma once

#include <StreamDeckSDK/ESDSDKDefines.h>

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
  ESDAction(ESDConnectionManager* esd_connection, const std::string& action, const std::string& context);
  virtual ~ESDAction();

  std::string GetAction() const;
  std::string GetContext() const;

  virtual void DidReceiveSettings(const nlohmann::json& settings);
  virtual void KeyDown(const nlohmann::json& settings);
  virtual void KeyUp(const nlohmann::json& settings);
  virtual void DialUp(const nlohmann::json& settings);
  virtual void DialDown(const nlohmann::json& settings);
  virtual void SendToPlugin(const nlohmann::json& payload);
  virtual void WillAppear(const nlohmann::json& settings);
  virtual void RotateClockwise(
    const nlohmann::json& settings,
    const unsigned int ticks,
    const bool pressed
  );
  virtual void RotateCounterClockwise(
    const nlohmann::json& settings,
    const unsigned int ticks,
    const bool pressed
  );

 protected:
  ESDConnectionManager* GetESD() const;

  // Convenience wrappers for GetESD()->foo()
  void SetState(int state);
  void SetTitle(
    const std::string& title,
    ESDSDKTarget = kESDSDKTarget_HardwareAndSoftware,
    int state = -1
  );
  void SetImage(
    const std::string& inBase64ImageString,
    ESDSDKTarget = kESDSDKTarget_HardwareAndSoftware,
    int state = -1
  );
  void ShowAlert();
  void ShowOK();
  void SetSettings(const nlohmann::json& inSettings);
  void SendToPropertyInspector(const nlohmann::json& inSettings);

 private:
  std::string mAction;
  std::string mContext;
  ESDConnectionManager* mESDConnection = nullptr;
};
