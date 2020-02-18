//
// Created by popov on 31.07.2019.
//

#ifndef BLACKENGINE_MOUSE_H
#define BLACKENGINE_MOUSE_H

namespace black {
enum class MouseButton {
  LEFT,
  RIGHT,
  MIDDLE
};

enum class MouseButtonAction {
  RELEASED,
  PRESSED,
};

struct MouseButtonEvent {
  MouseButton button;
  MouseButtonAction action;
  int modifiers; // see KEY_MODIFIER_ enum in Keyboard.h
};

struct MouseMovedEvent {
  float x, y;
};

struct ScrollEvent {
  float offsetX, offsetY;
};

}

#endif //BLACKENGINE_MOUSE_H
