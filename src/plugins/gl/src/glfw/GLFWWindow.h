//
// Created by popof on 02.10.2018.
//

#ifndef BLACKENGINE_GLFWWINDOW_H
#define BLACKENGINE_GLFWWINDOW_H

#include "../OpenGLCommonHeaders.h"

#include <render/AbstractRenderWindow.h>
#include <input/InputSystemInterface.h>

namespace black {
class GLFWWindow : public AbstractRenderWindow, public InputSystemInterface {
  using Cursor = std::unique_ptr<GLFWcursor, void (*)(GLFWcursor *)>;

  std::unique_ptr<GLFWwindow, void (*)(GLFWwindow *)> window;

  std::unordered_map<std::string, Cursor> cursors;

  bool isWindowShown;
  double mouseX, mouseY;

  std::string currentCursorName;
public:

  /**
   * Construct a glfw window. Does not show it.
   *
   * {@inheritDoc}
   */
  explicit GLFWWindow(WindowData data);

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

  void close() override;

  // InputSystemInterface
  bool isKeyPressed(Key key) override;
  bool isKeyPressed(int key) override;

  bool isKeyReleased(Key key) override;

  bool isKeyReleased(int key) override;

  void setCursorMode(CursorMode mode) override;
  void setMouseAccelerated(bool accelerated) override;

  void addCursor(std::string name, const Image &image) override;

  void setCursor(std::string name) override;

private:
  void initializeContext();
  void initializeWindowAndContext();
};
}

#endif //BLACKENGINE_GLFWWINDOW_H
