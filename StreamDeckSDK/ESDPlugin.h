/* Copyright (c) 2018, Corsair Memory, Inc.
 * Copyright (c) 2020-present, Fred Emmott
 *
 * This source code is licensed under the MIT-style license found in the
 * LICENSE file.
 */

#include <StreamDeckSDK/ESDBasePlugin.h>

#include <memory>

class ESDAction;

/** Coordinator class for `ESDAction`-based plugins.
 *
 * Plugins should:
 * - create one or more subclasses of `ESDAction`, one for each action type.
 * - create exactly one subclass of `ESDPlugin`, which implements
 *   `GetOrCreateAction()` to retrieve instances of an `ESDAction`.
 */
class ESDPlugin : public ESDBasePlugin {
 protected:
  /** Create or retrieve an ESDAction instance for the given action/context.
   *
   * Return a null/empty shared_ptr if the action is unrecognized.
   */
  virtual std::shared_ptr<ESDAction>
  GetOrCreateAction(const std::string& action, const std::string& context) = 0;

 public:
  ESDPlugin();
  virtual ~ESDPlugin();

	virtual void KeyDownForAction(
		const std::string& inAction,
		const std::string& inContext,
		const nlohmann::json& inPayload,
		const std::string& inDeviceID) override;

  virtual void KeyUpForAction(
    const std::string& inAction,
    const std::string& inContext,
    const nlohmann::json& inPayload,
    const std::string& inDeviceID) override;

  virtual void DialPressForAction(
    const std::string& inAction,
    const std::string& inContext,
    const nlohmann::json& inPayload,
    const std::string& inDeviceID) override;

  virtual void DialRotateForAction(
    const std::string& inAction,
    const std::string& inContext,
    const nlohmann::json& inPayload,
    const std::string& inDeviceID) override;

  virtual void WillAppearForAction(
    const std::string& inAction,
    const std::string& inContext,
    const nlohmann::json& inPayload,
    const std::string& inDeviceID) override;

  virtual void SendToPlugin(
    const std::string& inAction,
    const std::string& inContext,
    const nlohmann::json& inPayload,
    const std::string& inDevice) override;

  virtual void DidReceiveSettings(
    const std::string& inAction,
    const std::string& inContext,
    const nlohmann::json& inPayload,
    const std::string& inDevice) override;
};
