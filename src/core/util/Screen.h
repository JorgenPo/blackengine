//
// Created by popof on 15.11.2018.
//

#ifndef BLACKENGINE_SCREEN_H
#define BLACKENGINE_SCREEN_H

#include <CommonHeaders.h>

namespace black {

/**
 * Screen (main renderer window) parameters helper class
 */
class BLACK_EXPORTED Screen {
public:
  /**
   * Returns the screen aspect ratio. If the render system hasn't been initialized yet then
   * returns 0.0f.
   *
   * @return Main renderer window aspect ratio (width / height)
   */
  static float GetAspectRatio();

  /**
   * Returns the screen width. If the render system hasn't been initialized yet then
   * returns 0.
   *
   * @return Screen width
   */
  static int GetWidth();

  /**
   * Returns the screen height. If the render system hasn't been initialized yet then
   * returns 0.
   *
   * @return Screen height
   */
  static int GetHeight();
};
}

#endif //BLACKENGINE_SCREEN_H
