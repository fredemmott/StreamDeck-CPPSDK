/* Copyright (c) 2018, Corsair Memory, Inc.
 * Copyright (c) 2020-present, Fred Emmott
 *
 * This source code is licensed under the MIT-style license found in the
 * LICENSE file.
 */

#include "ESDPlugin.h"

#include <StreamDeckSDK/EPLJSONUtils.h>
#include <StreamDeckSDK/ESDConnectionManager.h>
#include <StreamDeckSDK/ESDLogger.h>

#include <atomic>
#include <mutex>

#include "ESDAction.h"

using json = nlohmann::json;

ESDPlugin::ESDPlugin() : ESDBasePlugin() {
}

ESDPlugin::~ESDPlugin() {
}

void ESDPlugin::KeyDownForAction(
  const std::string& inAction,
  const std::string& inContext,
  const json& inPayload,
  const std::string& inDeviceID) {
  auto action = GetOrCreateAction(inAction, inContext);
  if (!action) {
    ESDLog("No action for keydown - {} {}", inAction, inContext);
    return;
  }
  action->KeyDown(inPayload["settings"]);
}

void ESDPlugin::KeyUpForAction(
  const std::string& inAction,
  const std::string& inContext,
  const json& inPayload,
  const std::string& inDeviceID) {
  auto action = GetOrCreateAction(inAction, inContext);
  if (!action) {
    ESDLog("No action for keyup - {} {}", inAction, inContext);
    return;
  }
  action->KeyUp(inPayload["settings"]);
}

void ESDPlugin::DialPressForAction(
  const std::string& inAction,
  const std::string& inContext,
  const json& inPayload,
  const std::string& inDeviceID) {
  auto action = GetOrCreateAction(inAction, inContext);
  if (!action) {
    ESDLog("No action for dialPress - {} {}", inAction, inContext);
    return;
  }
  if (inPayload["pressed"])
    action->DialDown(inPayload["settings"]);
  else
    action->DialUp(inPayload["settings"]);
}

void ESDPlugin::DialRotateForAction(
  const std::string& inAction,
  const std::string& inContext,
  const json& inPayload,
  const std::string& inDeviceID) {
  auto action = GetOrCreateAction(inAction, inContext);
  if (!action) {
    ESDLog("No action for dialRotate - {} {}", inAction, inContext);
    return;
  }
  int ticks(inPayload["ticks"]);
  bool pressed(inPayload["pressed"]);
  if (inPayload["ticks"] < 0) {
    action->RotateCounterClockwise(
      inPayload["settings"], static_cast<const unsigned int>(-ticks), pressed);
  } else {
    action->RotateClockwise(
      inPayload["settings"], static_cast<const unsigned int>(ticks), pressed);
  }
}

void ESDPlugin::WillAppearForAction(
  const std::string& inAction,
  const std::string& inContext,
  const json& inPayload,
  const std::string& inDeviceID) {
  auto action = GetOrCreateAction(inAction, inContext);
  if (!action) {
    ESDLog("No action for WillAppear - {} {}", inAction, inContext);
    return;
  }
  action->WillAppear(inPayload["settings"]);
}

void ESDPlugin::SendToPlugin(
  const std::string& inAction,
  const std::string& inContext,
  const json& inPayload,
  const std::string& inDevice) {
  auto action = GetOrCreateAction(inAction, inContext);
  if (!action) {
    ESDLog(
      "Received plugin request for unknown action {} {}", inAction, inContext);
    return;
  }
  action->SendToPlugin(inPayload);
}

void ESDPlugin::DidReceiveSettings(
  const std::string& inAction,
  const std::string& inContext,
  const json& inPayload,
  const std::string& inDevice) {
  auto action = GetOrCreateAction(inAction, inContext);
  if (!action) {
    ESDLog("No action for DidReceiveSettings: {} {}", inAction, inContext);
    return;
  }
  action->DidReceiveSettings(inPayload["settings"]);
}
