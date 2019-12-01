//
// Created by popof on 29.09.2018.
//

#ifndef BLACKENGINE_RENDERTARGETINTERFACE_H
#define BLACKENGINE_RENDERTARGETINTERFACE_H

#include "../common/CommonHeaders.h"

#include <BlackEngine/common/events/EventPublisher.h>

namespace black {

struct RenderTargetSizeChanged {
  float width;
  float height;
};

/**
 * Represents an object on which render can render.
 */
class RenderTargetInterface : public EventPublisher<RenderTargetSizeChanged> {

public:
  using EventPublisher<RenderTargetSizeChanged>::publish;

  /**
   * Updates a renderer target.
   */
  virtual void updateRenderTarget() = 0;

  /**
   * Makes a renderer target current
   */
  virtual void setRenderTargetCurrent() = 0;

  /**
   * Returns a width of the render target
   *
   * @return Width of the render target
   */
  virtual float getRenderTargetWidth() = 0;

  /**
   * Returns a height of the render target
   *
   * @return Width of the render target
   */
  virtual float getRenderTargetHeight() = 0;

  /**
   * Returns a width of the render target
   *
   * @return Width of the render target
   */
  virtual float getRenderTargetAspectRatio() = 0;
};

}

#endif //BLACKENGINE_RENDERTARGETINTERFACE_H
