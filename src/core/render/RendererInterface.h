//
// Created by popof on 29.09.2018.
//

#ifndef BLACKENGINE_RENDERERINTERFACE_H
#define BLACKENGINE_RENDERERINTERFACE_H

#include <CommonHeaders.h>
#include <exceptions/Exception.h>

#include <vector>

namespace black {
class GameObject;
class Camera;
class RenderTargetInterface;
class AbstractScene;

class RendererInitializationException : public Exception {
public:
  explicit RendererInitializationException(const std::string &message) : Exception(message) {}
};

class BLACK_EXPORTED RendererInterface {
public:
  virtual void setCurrentRenderTarget(std::shared_ptr<RenderTargetInterface> target) = 0;

  /**
   * Renders a next frame
   */
  virtual void render(const std::shared_ptr<AbstractScene> &scene) = 0;

  /**
   * Set renderer viewport so all rendering will be in this bounds.
   *
   * @param x         X coordinate of the lower left corner
   * @param y         Y coordinate of the lower left corner
   * @param width     Width of the viewport
   * @param height    Height of the viewport
   */
  virtual void setViewPort(int x, int y, int width, int height) = 0;
};
}

#endif //BLACKENGINE_RENDERERINTERFACE_H
