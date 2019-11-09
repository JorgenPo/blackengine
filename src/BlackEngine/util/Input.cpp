//
// Created by popof on 19.11.2018.
//

#include "Input.h"

#include "../SystemInterface.h"
#include "../Engine.h"

#include <BlackEngine/input/KeyboardEventEmitter.h>
#include <BlackEngine/render/RenderSystemInterface.h>

namespace black {

double Input::mouseX = 0;
double Input::mouseY = 0;
std::shared_ptr<InputSystemInterface> Input::input = nullptr;

bool Input::IsKeyPressed(Key key) {
  return Input::IsKeyPressed(static_cast<int>(key));
}

bool Input::IsKeyPressed(int key) {
  return input->isKeyPressed(key);
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
  return input->isKeyReleased(key);
}

bool Input::IsKeyReleased(int key) {
  return IsKeyReleased(Key(key));
}

void Input::AddCursor(std::string_view name, const Image &image) {
  input->addCursor(name.data(), image);
}

void Input::SetCursor(std::string_view name) {
  input->setCursor(name.data());
}

void Input::Initialize(std::shared_ptr<InputSystemInterface> inputInterface) {
  input = std::move(inputInterface);
}

}