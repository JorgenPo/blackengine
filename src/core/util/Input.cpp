//
// Created by popof on 19.11.2018.
//

#include "Input.h"

#include <input/KeyboardEventEmitter.h>
#include <render/RenderSystemInterface.h>
#include <Engine.h>

namespace black {

double Input::mouseX = 0;
double Input::mouseY = 0;

bool Input::IsKeyPressed(Key key) {
  return Input::IsKeyPressed(static_cast<int>(key));
}

bool Input::IsKeyPressed(int key) {
  auto systemInterface = Engine::GetCurrentRenderSystem()->getSystemInterface();
  if (!systemInterface) {
    return false;
  }

  return systemInterface->isKeyPressed(key);
}

void Input::OnMousePositionChanged(double x, double y) {
  mouseY = y;
  mouseX = x;
}

double Input::GetMouseY() {
  return mouseY;
}

double Input::GetMouseX() {
  return mouseX;
}

bool Input::IsKeyReleased(Key key) {
  auto systemInterface = Engine::GetCurrentRenderSystem()->getSystemInterface();
  if (!systemInterface) {
    return false;
  }

  return systemInterface->isKeyReleased(key);
}

bool Input::IsKeyReleased(int key) {
  return IsKeyReleased(Key(key));
}

void Input::AddCursor(std::string_view name, const Image &image) {
  auto systemInterface = Engine::GetCurrentRenderSystem()->getSystemInterface();
  if (!systemInterface) {
    return;
  }

  systemInterface->addCursor(name.data(), image);
}

void Input::SetCursor(std::string_view name) {
  auto systemInterface = Engine::GetCurrentRenderSystem()->getSystemInterface();
  if (!systemInterface) {
    return;
  }

  systemInterface->setCursor(name.data());
}

std::shared_ptr<KeyboardEventEmitter> Input::GetKeyboardEventEmitter() {
  auto systemInterface = Engine::GetCurrentRenderSystem()->getSystemInterface();
  if (!systemInterface) {
    return nullptr;
  }

  return systemInterface;
}

std::shared_ptr<MouseEventEmitter> Input::GetMouseEventEmitter() {
  auto systemInterface = Engine::GetCurrentRenderSystem()->getSystemInterface();
  if (!systemInterface) {
    return nullptr;
  }

  return systemInterface;
}

}