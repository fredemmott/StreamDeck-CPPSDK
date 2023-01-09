/* Copyright (c) 2020-present, Fred Emmott
 *
 * This source code is licensed under the MIT-style license found in the
 * LICENSE file.
 */

#include "ESDAction.h"

#include <StreamDeckSDK/ESDConnectionManager.h>

ESDAction::ESDAction(
  ESDConnectionManager* esd_connection,
  const std::string& action,
  const std::string& context)
  : mESDConnection(esd_connection), mAction(action), mContext(context) {
}

ESDAction::~ESDAction() {
}

std::string ESDAction::GetContext() const {
  return mContext;
}

std::string ESDAction::GetAction() const {
  return mAction;
}

void ESDAction::DidReceiveSettings(const nlohmann::json& json) {
}

ESDConnectionManager* ESDAction::GetESD() const {
  return mESDConnection;
}

void ESDAction::KeyDown(const nlohmann::json& settings) {
}

void ESDAction::KeyUp(const nlohmann::json& settings) {
}

void ESDAction::DialUp(const nlohmann::json& settings) {
}

void ESDAction::DialDown(const nlohmann::json& settings) {
}

void ESDAction::RotateClockwise(
  const nlohmann::json& settings,
  const unsigned int ticks,
  const bool pressed) {
}

void ESDAction::RotateCounterClockwise(
  const nlohmann::json& settings,
  const unsigned int ticks,
  const bool pressed) {
}

void ESDAction::SendToPlugin(const nlohmann::json& payload) {
}

void ESDAction::WillAppear(const nlohmann::json& settings) {
}

void ESDAction::SetState(int state) {
  GetESD()->SetState(state, mContext);
}

void ESDAction::SetTitle(
  const std::string& title,
  ESDSDKTarget target,
  int state) {
  GetESD()->SetTitle(title, mContext, target, state);
}
void ESDAction::SetImage(
  const std::string& inBase64ImageString,
  ESDSDKTarget target,
  int state) {
  GetESD()->SetImage(inBase64ImageString, mContext, target, state);
}
void ESDAction::SetSettings(const nlohmann::json& inSettings) {
  GetESD()->SetSettings(inSettings, mContext);
}
void ESDAction::ShowAlert() {
  GetESD()->ShowAlertForContext(mContext);
}
void ESDAction::ShowOK() {
  GetESD()->ShowOKForContext(mContext);
}
void ESDAction::SetFeedback(const nlohmann::json& inPayload) {
  GetESD()->SetFeedback(inPayload, mContext);
}

void ESDAction::SetFeedbackLayout(const std::string& inIdentifierOrPath) {
  GetESD()->SetFeedbackLayout(inIdentifierOrPath, mContext);
}

void ESDAction::SendToPropertyInspector(const nlohmann::json& payload) {
  GetESD()->SendToPropertyInspector(mAction, mContext, payload);
}
