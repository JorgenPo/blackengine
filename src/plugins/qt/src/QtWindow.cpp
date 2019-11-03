#include "QtWindow.h"

#include "QtWindowImpl.h"

namespace black {

void QtWindow::show() {
  impl->show();
}

void QtWindow::hide() {
  impl->hide();
}

void QtWindow::close() {
  impl->close();
}

bool QtWindow::isShown() {
  return impl->isVisible();
}

void QtWindow::pollEvents() {

}

bool QtWindow::shouldClose() {
  return false;
}

void QtWindow::updateRenderTarget() {
  impl->swapBuffers();
}

void QtWindow::setRenderTargetCurrent() {
  impl->setContextCurrent();
}

float QtWindow::getRenderTargetWidth() {
  return static_cast<float>(impl->width());
}

float QtWindow::getRenderTargetHeight() {
  return static_cast<float>(impl->height());
}

float QtWindow::getRenderTargetAspectRatio() {
  return getRenderTargetWidth() / getRenderTargetHeight();
}


QtWindow::QtWindow(const std::string &title, int width, int height, bool isFullScreen)
  : AbstractRenderWindow(
    WindowData{
      title,
      width,
      height,
      isFullScreen,
      ContextVersion{4, 0}}),
    impl() {
}

}