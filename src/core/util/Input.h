//
// Created by popof on 19.11.2018.
//

#ifndef BLACKENGINE_INPUT_H
#define BLACKENGINE_INPUT_H

#include <CommonHeaders.h>

#include <input/SystemInterface.h>

namespace black {
/**
 * User input utils
 */
class BLACK_EXPORTED Input {
public:
  static bool IsKeyPressed(Key key);
  static bool IsKeyPressed(int key);
};

}
#endif //BLACKENGINE_INPUT_H
