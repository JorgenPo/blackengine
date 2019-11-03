#ifndef BLACKENGINE_QTWINDOW_H
#define BLACKENGINE_QTWINDOW_H

#include <render/AbstractRenderWindow.h>
#include <input/InputSystemInterface.h>

// Implementation of window and system interface
// based on qt library

namespace black {

class QtWindowImpl;

class QtWindow : public AbstractRenderWindow {
  std::shared_ptr<QtWindowImpl> impl;

public:
  QtWindow(const std::string &title, int width, int height, bool isFullScreen);

  // AbstractRenderWindow
  void show() override;
  void hide() override;
  void close() override;
  bool isShown() override;
  void pollEvents() override;
  bool shouldClose() override;

  // RenderTargetInterface
  void updateRenderTarget() override;
  void setRenderTargetCurrent() override;
  float getRenderTargetWidth() override;
  float getRenderTargetHeight() override;
  float getRenderTargetAspectRatio() override;
};

}

#endif //BLACKENGINE_QTWINDOW_H
