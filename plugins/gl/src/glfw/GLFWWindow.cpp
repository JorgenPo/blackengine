//
// Created by popof on 02.10.2018.
//

#include "GLFWWindow.h"

#include <BlackEngine/Image.h>
#include <BlackEngine/Engine.h>

#include <BlackEngine/render/RenderSystemInterface.h>
#include <BlackEngine/SystemInterface.h>

#include <BlackEngine/log/Logger.h>

namespace black {

GLFWWindow::GLFWWindow(WindowData data)
    : AbstractRenderWindow(std::move(data)),
      window(nullptr, nullptr),
      isWindowShown(false),
      mouseX(0),
      mouseY(0) {
  initializeWindowAndContext();
}

void GLFWWindow::updateRenderTarget() {
  glfwSwapBuffers(this->window.get());
}

void GLFWWindow::setRenderTargetCurrent() {
  glfwMakeContextCurrent(this->window.get());
}

float GLFWWindow::getRenderTargetWidth() const {
  return static_cast<float>(data.width);
}

float GLFWWindow::getRenderTargetHeight() const {
  return static_cast<float>(data.height);
}

float GLFWWindow::getRenderTargetAspectRatio() {
  return static_cast<float>(data.width) / static_cast<float>(data.height);
}

void GLFWWindow::show() {
  glfwShowWindow(this->window.get());
  this->isWindowShown = true;
}

void GLFWWindow::hide() {
  glfwHideWindow(this->window.get());
  this->isWindowShown = false;
}

bool GLFWWindow::isShown() {
  return this->isWindowShown;
}

bool GLFWWindow::shouldClose() {
  return glfwWindowShouldClose(this->window.get()) == GL_TRUE;
}

void GLFWWindow::pollEvents() {
  scrollX = 0;
  scrollY = 0;
  glfwPollEvents();
}

bool GLFWWindow::isKeyPressed(Key key) {
  return glfwGetKey(this->window.get(), static_cast<int>(key)) == GLFW_PRESS;
}

bool GLFWWindow::isKeyPressed(int key) {
  return glfwGetKey(this->window.get(), key) == GLFW_PRESS;
}

void GLFWWindow::setMouseAccelerated(bool accelerated) {
  if (glfwRawMouseMotionSupported()) {
    glfwSetInputMode(window.get(), GLFW_RAW_MOUSE_MOTION, accelerated);
  }
}

void GLFWWindow::setCursorMode(CursorMode mode) {
  isCursorDisabled = false;

  switch (mode) {
    case CursorMode::CAPTURED:
      glfwSetInputMode(window.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
      isCursorDisabled = true;
      break;
    case CursorMode::VISIBLE:
      glfwSetInputMode(window.get(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
      break;
    case CursorMode::HIDDEN:
      glfwSetInputMode(window.get(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
      break;
  }
}

void GLFWWindow::close() {
  glfwSetWindowShouldClose(window.get(), true);
}

bool GLFWWindow::isKeyReleased(Key key) {
  return glfwGetKey(this->window.get(), static_cast<int>(key)) == GLFW_RELEASE;
}

bool GLFWWindow::isKeyReleased(int key) {
  return glfwGetKey(this->window.get(), key) == GLFW_RELEASE;
}

void GLFWWindow::addCursor(std::string name, const Image &image) {
  GLFWimage glfwImage;
  glfwImage.width = image.getWidth();
  glfwImage.height = image.getHeight();
  glfwImage.pixels = image.getData();

  auto glfwCursor = glfwCreateCursor(&glfwImage, 0, 0);
  auto cursor = std::unique_ptr<GLFWcursor, void (*)(GLFWcursor *)>(glfwCursor, glfwDestroyCursor);
  cursors.insert(std::make_pair(std::move(name), std::move(cursor)));
}

void GLFWWindow::setCursor(std::string name) {
  if (name == currentCursorName) {
    return;
  }

  try {
    auto &cursor = cursors.at(name);
    glfwSetCursor(this->window.get(), cursor.get());
    currentCursorName = std::move(name);
  } catch (const std::out_of_range &e) {
    Logger::Get("GLFWWindow")->warning("Cursor '{}' not found", name);
    return;
  }
}

void GLFWWindow::initializeContext() {
  Logger::Get("GLFWWindow")->info("Initializing OpenGL {0}.{1} context using GLFW and GLAD",
    data.contextVersion.major, data.contextVersion.minor);

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, data.contextVersion.major);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, data.contextVersion.minor);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef BLACK_PLATFORM_MACOSX
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

void GLFWWindow::initializeWindowAndContext() {
  initializeContext();

  // Init GLFW window
  auto glfwWindow = glfwCreateWindow(
    getWidth(), getHeight(), getTitle().c_str(), nullptr, nullptr);

  if (glfwWindow == nullptr) {
    throw RenderWindowInitializationException("Failed to initialize glfw window");
  }

  glfwSetWindowUserPointer(glfwWindow, this);

  this->window = std::unique_ptr<GLFWwindow, void (*)(GLFWwindow *)>(glfwWindow, glfwDestroyWindow);

  glfwSetFramebufferSizeCallback(this->window.get(), [](GLFWwindow *win, int width, int height) {
    glViewport(0, 0, width, height);
    auto that = (GLFWWindow *)(glfwGetWindowUserPointer(win));

    that->data.width = width;
    that->data.height = height;

    dynamic_cast<RenderTargetInterface*>(that)->publish((float) width, (float) height);
  });

  glfwSetCursorPosCallback(this->window.get(), [](GLFWwindow *win, double x, double y) {
    auto that = (GLFWWindow*)(glfwGetWindowUserPointer(win));
    that->mouseX = x;
    that->mouseY = y;

    that->publishMouseMovedEvent(MouseMovedEvent{
      static_cast<float>(x), static_cast<float>(y)
    });
  });

  glfwSetKeyCallback(this->window.get(), [](GLFWwindow *win, int key, int scanCode, int action, int modifiers) {
    KeyEvent event{Key{key}, scanCode, KeyAction{action}, modifiers};
    auto that = (GLFWWindow*)(glfwGetWindowUserPointer(win));

    that->publishKeyEvent(event);
  });

  glfwSetMouseButtonCallback(this->window.get(), [](GLFWwindow *win, int button, int action, int modifiers) {
    MouseButtonEvent event{MouseButton{button}, MouseButtonAction{action}, modifiers};
    auto that = (GLFWWindow*)(glfwGetWindowUserPointer(win));

    that->publishMouseButtonEvent(event);
  });

  glfwSetScrollCallback(this->window.get(), [](GLFWwindow *win, double xOffset, double yOffset) {
    auto that = (GLFWWindow*)(glfwGetWindowUserPointer(win));
    that->publishScrollEvent(ScrollEvent{static_cast<float>(xOffset), static_cast<float>(yOffset)});
    that->scrollX = xOffset;
    that->scrollY = yOffset;
  });

  setRenderTargetCurrent();

  // Init GLAD
  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    glfwTerminate();
    throw RenderWindowInitializationException("Failed to initialize OpenGL Context");
  }
}

float GLFWWindow::getMouseX() const noexcept {
  return static_cast<float>(mouseX);
}

float GLFWWindow::getMouseY() const noexcept {
  return static_cast<float>(mouseY);
}

float GLFWWindow::getScrollX() const {
  return static_cast<float>(scrollX);
}

float GLFWWindow::getScrollY() const {
  return static_cast<float>(scrollY);
}

}