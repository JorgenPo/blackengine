#ifndef BLACKENGINE_QTWINDOWIMPL_H
#define BLACKENGINE_QTWINDOWIMPL_H

#include <qt/QtGui/QWindow>
#include <qt/QtGui/QOpenGLFunctions>

#include <memory>

class QOpenGLPaintDevice;

namespace black {

class QtWindowImpl : public QWindow {
  Q_OBJECT

  std::shared_ptr<QOpenGLContext> context;
  std::shared_ptr<QOpenGLPaintDevice> device;

public:
  explicit QtWindowImpl(QWindow *parent = nullptr);
  ~QtWindowImpl() = default;

  void setContextCurrent();
  void swapBuffers();
};

}


#endif //BLACKENGINE_QTWINDOWIMPL_H
