//
// Created by popof on 30.09.2018.
//

#ifndef BLACKENGINE_RENDERWINDOWINTERFACE_H
#define BLACKENGINE_RENDERWINDOWINTERFACE_H

#include "RenderTargetInterface.h"

#include "../common/CommonHeaders.h"
#include "../exceptions/Exception.h"

#include <BlackEngine/input/MouseEventPublisher.h>
#include <BlackEngine/input/KeyboardEventPublisher.h>
#include <BlackEngine/input/InputSystemInterface.h>

namespace black {

class InputSystemInterface;

class BLACK_EXPORTED RenderWindowInitializationException : public Exception {
public:
  explicit RenderWindowInitializationException(const std::string &message) : Exception(message) {}
};

struct ContextVersion {
  int major;
  int minor;
};

// Data required for initialization
struct WindowData {
  std::string title;
  int width;
  int height;
  bool isFullScreen = false;
  ContextVersion contextVersion = {3, 0};
};

/**
 * Interface for render window.
 */
class BLACK_EXPORTED AbstractRenderWindow :
  public RenderTargetInterface {

protected:
  WindowData data;

public:

  /**
   * Construct a window and initialize context
   *
   * @param title            Window title
   * @param width            Window width
   * @param height           Window height
   * @param isFullScreen     Is full screen
   */
  explicit AbstractRenderWindow(WindowData data) :
      data(std::move(data)) {

  }

  virtual void show() = 0;
  virtual void hide() = 0;
  virtual void close() = 0;
  virtual bool isShown() = 0;
  virtual void pollEvents() = 0;

  /**
   * Is the window should be closed.
   *
   * @return True if window should be closed
   */
  virtual bool shouldClose() = 0;

  [[nodiscard]] const std::string &getTitle() const {
    return data.title;
  }

  [[nodiscard]] bool isFullScreen() {
    return data.isFullScreen;
  }

  [[nodiscard]] int getHeight() const {
    return data.height;
  }

  [[nodiscard]] int getWidth() const {
    return data.width;
  }

  void setWidth(int newWidth) {
    data.width = newWidth;
  }

  void setTitle(std::string title) {
    data.title = std::move(title);
  }

  void setHeight(int newHeight) {
    data.height = newHeight;
  }

  void setFullScreen(bool isFullScreen) {
    data.isFullScreen = isFullScreen;
  }
};
}

#endif //BLACKENGINE_RENDERWINDOWINTERFACE_H
