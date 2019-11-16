//
// Created by popof on 15.11.2018.
//

#ifndef BLACKENGINE_SCREEN_H
#define BLACKENGINE_SCREEN_H

#include "../common/CommonHeaders.h"

#include <memory>

namespace black {

class RendererInterface;

/**
 * Screen (main renderer window) parameters helper class
 */
class BLACK_EXPORTED Screen {
  static std::shared_ptr<RendererInterface> renderer;

public:
  static void Initialize(std::shared_ptr<RendererInterface> renderer) noexcept;

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
