#include <glad/glad.h>
#include "renderwindow.h"
#include "mainwindow.h"

#include <BlackEngine/Engine.h>
#include <BlackEngine/log/Logger.h>
#include <BlackEngine/components/BoundingComponent.h>
#include <BlackEngine/camera/Camera.h>
#include <BlackEngine/render/RenderSystemInterface.h>

#include <QMouseEvent>
#include <utility>

using namespace black;
using namespace blackeditor;

RenderWindow::RenderWindow(std::shared_ptr<MainWindow> mainWindow) :
    QOpenGLWidget(mainWindow.get())
    , AbstractRenderWindow(black::WindowData{
      "BlackEngine",this->width(), this->height(),
      false, {4, 3}})
    , scene(nullptr)
    , mainWindow(std::move(mainWindow))
{
    QSurfaceFormat contextInfo;
    contextInfo.setVersion(getContextVersion().major, getContextVersion().minor);
    contextInfo.setProfile(QSurfaceFormat::CoreProfile);
    this->setFormat(contextInfo);
}

void RenderWindow::setInput(std::shared_ptr<black::InputSystemInterface> newInput) {
  this->input = std::move(newInput);
}

void RenderWindow::initializeGL()
{
    // Init GLAD
    if (gladLoadGL()) {
        renderer = Engine::GetCurrentRenderSystem()->createRenderer(shared_from_this());
    } else {
        Logger::Get("RenderWindow")->critical("Failed to init opengl functions");
    }

    scene = std::make_shared<Scene>(shared_from_this(), input);
    scene->initialize();
    mainWindow->onSceneInitialized();
}

void RenderWindow::resizeGL(int w, int h)
{
  renderer->setViewPort(0, 0, w, h);
  this->publish(RenderTargetSizeChanged{static_cast<float>(w), static_cast<float>(h)});
}

void RenderWindow::paintGL()
{
    renderer->render(scene->get());
}


void RenderWindow::updateRenderTarget()
{
    scene->update(isFocused);
    this->repaint();
}

void RenderWindow::setRenderTargetCurrent()
{
    this->makeCurrent();
}

float RenderWindow::getRenderTargetWidth() const
{
    return this->width();
}

float RenderWindow::getRenderTargetHeight() const
{
    return this->height();
}

float RenderWindow::getRenderTargetAspectRatio()
{
    return (float)this->width() / (float)this->height();
}

void RenderWindow::show()
{
    QOpenGLWidget::show();
}

void RenderWindow::hide()
{
    QOpenGLWidget::hide();
}

void RenderWindow::close()
{
    QOpenGLWidget::close();
}

bool RenderWindow::isShown()
{
    return QOpenGLWidget::isVisible();
}

void RenderWindow::pollEvents()
{
}

bool RenderWindow::shouldClose()
{
    return false;
}

std::shared_ptr<Scene> RenderWindow::getScene() const noexcept {
  return scene;
}

std::string RenderWindow::getOpenGLVersionString() const {
  return fmt::format("{}.{}", format().majorVersion(), format().minorVersion());
}

std::string RenderWindow::getGLSLVersionString() const {
  return reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));
}

std::string RenderWindow::getProfileString() const {
  if (this->context()->format().profile() == QSurfaceFormat::OpenGLContextProfile::CoreProfile) {
    return "Core";
  } else {
    return "Compatibility";
  }
}

void RenderWindow::mousePressEvent(QMouseEvent *event) {
  scene->mousePressEvent(event);
  this->setFocus();
}

void RenderWindow::keyPressEvent(QKeyEvent *event) {
  scene->keyPressEvent(event);
}

void RenderWindow::enterEvent(QEvent *event) {
  isFocused = true;
}

void RenderWindow::leaveEvent(QEvent *event) {
  isFocused = false;
}

void RenderWindow::setMainWindow(std::shared_ptr<MainWindow> newMainWindow) {
  mainWindow = std::move(newMainWindow);
}
