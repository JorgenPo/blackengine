#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include "editor/Scene.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_4_Core>

#include <BlackEngine/render/AbstractRenderWindow.h>
#include <BlackEngine/render/RendererInterface.h>
#include <BlackEngine/scene/SimpleScene.h>

#include <memory>

namespace blackeditor {

class RenderWindow :
    public QOpenGLWidget,
    public black::AbstractRenderWindow,
    public std::enable_shared_from_this<RenderWindow> {

  std::shared_ptr<black::RendererInterface> renderer;
  std::shared_ptr<Scene> scene;
  std::shared_ptr<black::InputSystemInterface> input;
  bool isFocused = false;

public:
  explicit RenderWindow(QWidget *parent);

  void setInput(std::shared_ptr<black::InputSystemInterface> input);

  std::string getOpenGLVersionString() const;
  std::string getGLSLVersionString() const;
  std::string getProfileString() const;

protected:
  void mousePressEvent(QMouseEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;

  void enterEvent(QEvent *event) override;

  void leaveEvent(QEvent *event) override;

  // QOpenGLWidget interface
protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

  // RenderTargetInterface interface
public:
  void updateRenderTarget() override;
  void setRenderTargetCurrent() override;
  float getRenderTargetWidth() const override;
  float getRenderTargetHeight() const override;
  float getRenderTargetAspectRatio() override;

  // AbstractRenderWindow interface
  void show() override;
  void hide() override;
  void close() override;
  bool isShown() override;
  void pollEvents() override;
  bool shouldClose() override;


  std::shared_ptr<Scene> getScene() const noexcept;
};

}

#endif // RENDERWINDOW_H
