//
// Created by popof on 02.10.2018.
//

#ifndef BLACKENGINE_GLFWWINDOW_H
#define BLACKENGINE_GLFWWINDOW_H

#include "OpenGLCommonHeaders.h"

#include <render/AbstractRenderWindow.h>
#include <input/SystemInterface.h>

namespace black {
class GLFWWindow : public AbstractRenderWindow, public SystemInterface {
  std::unique_ptr<GLFWwindow, void (*)(GLFWwindow *)> window;

  bool isWindowShown;

public:

  /**
   * Construct a glfw window. Does not show it.
   *
   * {@inheritDoc}
   */
  GLFWWindow(const std::string &title, int width, int height, bool isFullScreen);

  // RenderTargetInterface
  void updateRenderTarget() override;
  void setRenderTargetCurrent() override;
  float getRenderTargetWidth() override;
  float getRenderTargetHeight() override;
  float getRenderTargetAspectRatio() override;

  // AbstractRenderWindow Interface

  void show() override;
  void hide() override;
  bool isShown() override;
  bool shouldClose() override;
  void pollEvents() override;

  // SystemInterface
  bool isKeyPressed(Key key) override;
  bool isKeyPressed(int key) override;
};
}

#endif //BLACKENGINE_GLFWWINDOW_H
