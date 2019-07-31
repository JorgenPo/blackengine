//
// Created by popof on 19.11.2018.
//

#ifndef BLACKENGINE_INPUT_H
#define BLACKENGINE_INPUT_H

#include <Image.h>

#include <common/CommonHeaders.h>

#include <input/SystemInterface.h>

namespace black {

class KeyboardEventEmitter;

/**
 * User input utils
 */
class BLACK_EXPORTED Input {
private:
  static double mouseX, mouseY;

public:
  static bool IsKeyPressed(Key key);
  static bool IsKeyPressed(int key);
  static bool IsKeyReleased(Key key);
  static bool IsKeyReleased(int key);

  static double GetMouseX();
  static double GetMouseY();

  static void OnMousePositionChanged(double x, double y);

  static void AddCursor(std::string_view name, const Image &image);
  static void SetCursor(std::string_view name);

  static std::shared_ptr<KeyboardEventEmitter> GetKeyboardEventEmitter();
  static std::shared_ptr<MouseEventEmitter> GetMouseEventEmitter();
};

}
#endif //BLACKENGINE_INPUT_H
