#include <utility>

//
// Created by popof on 30.09.2018.
//

#ifndef BLACKENGINE_RENDERWINDOWINTERFACE_H
#define BLACKENGINE_RENDERWINDOWINTERFACE_H

#include "RenderTargetInterface.h"

#include <CommonHeaders.h>
#include <exceptions/Exception.h>

namespace black {

class BLACK_EXPORTED RenderWindowInitializationException : public Exception {
public:
  RenderWindowInitializationException(const std::string &message) : Exception(message) {}
};

/**
 * Interface for render window.
 */
class BLACK_EXPORTED AbstractRenderWindow : public RenderTargetInterface {
protected:
  std::string title;
  int width;
  int height;
  bool fullScreen;

public:

  /**
   * Construct a window.
   *
   * @param title            Window title
   * @param width            Window width
   * @param height           Window height
   * @param isFullScreen     Is full screen
   */
  AbstractRenderWindow(std::string title, int width, int height, bool isFullScreen = false) :
      title(std::move(title)), width(width), height(height), fullScreen(isFullScreen) {

  }

  virtual void show() = 0;
  virtual void hide() = 0;
  virtual bool isShown() = 0;
  virtual void pollEvents() = 0;

  /**
   * Is the window should be closed.
   *
   * @return True if window should be closed
   */
  virtual bool shouldClose() = 0;

  const std::string &getTitle() const {
    return title;
  }

  void setTitle(const std::string &title) {
    AbstractRenderWindow::title = title;
  }

  int getWidth() const {
    return width;
  }

  void setWidth(int width) {
    AbstractRenderWindow::width = width;
  }

  int getHeight() const {
    return height;
  }

  void setHeight(int height) {
    AbstractRenderWindow::height = height;
  }

  bool isFullScreen() const {
    return fullScreen;
  }

  void setFullScreen(bool isFullScreen) {
    this->fullScreen = isFullScreen;
  }
};
}

#endif //BLACKENGINE_RENDERWINDOWINTERFACE_H
