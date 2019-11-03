#include "QtWindowImpl.h"

#include <qt/QtGui/QOpenGLPaintDevice>

namespace black {

QtWindowImpl::QtWindowImpl(QWindow *parent)
  : QWindow(parent), device(std::make_shared<QOpenGLPaintDevice>()) {
  setSurfaceType(SurfaceType::OpenGLSurface);

  QSurfaceFormat format;
  format.setProfile(QSurfaceFormat::CoreProfile);
  format.setVersion(3, 3);

  setFormat(format);

  context = std::make_shared<QOpenGLContext>(this);
  context->setFormat(requestedFormat());
}

void QtWindowImpl::setContextCurrent() {
  context->makeCurrent(this);
}

void QtWindowImpl::swapBuffers() {
  context->swapBuffers(this);
}


}