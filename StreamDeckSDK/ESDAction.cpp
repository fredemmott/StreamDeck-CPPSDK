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

void ESDAction::DidReceiveSettings(const nlohmann::json& json) {
}

ESDConnectionManager* ESDAction::GetESD() const {
  return mESDConnection;
}

void ESDAction::KeyUp(const nlohmann::json& settings) {
}

void ESDAction::SendToPlugin(const nlohmann::json& payload) {
}

void ESDAction::WillAppear(const nlohmann::json& settings) {
}

void ESDAction::SetState(int state) {
  GetESD()->SetState(state, mContext);
}

void ESDAction::SetTitle(const std::string& title, ESDSDKTarget target) {
  GetESD()->SetTitle(title, mContext, target);
}
void ESDAction::SetImage(
  const std::string& inBase64ImageString,
  ESDSDKTarget target) {
  GetESD()->SetImage(inBase64ImageString, mContext, target);
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

void ESDAction::SendToPropertyInspector(const nlohmann::json& payload) {
  GetESD()->SendToPropertyInspector(
    mAction,
    mContext,
    payload
  );
}
