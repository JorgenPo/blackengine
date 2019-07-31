//
// Created by popof on 02.10.2018.
//

#include "GLFWWindow.h"

#include <Image.h>
#include <Engine.h>

#include <render/RenderSystemInterface.h>
#include <util/Input.h>
#include <log/Logger.h>

namespace black {

GLFWWindow::GLFWWindow(const std::string &title, int width, int height, bool isFullScreen)
    : AbstractRenderWindow(title, width, height, isFullScreen),
      window(nullptr, nullptr),
      isWindowShown(false),
    mouseX(0), mouseY(0) {

  // Init GLFW window
  auto glfwWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

  if (glfwWindow == nullptr) {
    throw RenderWindowInitializationException("Failed to initialize glfw window");
  }

  this->window = std::unique_ptr<GLFWwindow, void (*)(GLFWwindow *)>(glfwWindow, glfwDestroyWindow);

  glfwSetFramebufferSizeCallback(this->window.get(), [](GLFWwindow */*window*/, int width, int height) {
    glViewport(0, 0, width, height);
  });

  glfwSetCursorPosCallback(this->window.get(), [](GLFWwindow *win, double x, double y) {
    Input::OnMousePositionChanged(x, y);
  });

  glfwSetKeyCallback(this->window.get(), [](GLFWwindow *win, int key, int scanCode, int action, int modifiers) {
    KeyEvent event{Key{key}, scanCode, KeyAction{action}, modifiers};
    Engine::GetCurrentRenderSystem()->getSystemInterface()->emitKeyPressedEvent(event);
  });

  glfwSetMouseButtonCallback(this->window.get(), [](GLFWwindow *win, int button, int action, int modifiers) {
    MouseButtonEvent event{MouseButton{button}, MouseButtonAction{action}, modifiers};
    Engine::GetCurrentRenderSystem()->getSystemInterface()->emitMouseButtonEvent(event);
  });
}

void GLFWWindow::updateRenderTarget() {
  glfwSwapBuffers(this->window.get());
}

void GLFWWindow::setRenderTargetCurrent() {
  glfwMakeContextCurrent(this->window.get());
}

float GLFWWindow::getRenderTargetWidth() {
  return static_cast<float>(width);
}

float GLFWWindow::getRenderTargetHeight() {
  return static_cast<float>(height);
}

float GLFWWindow::getRenderTargetAspectRatio() {
  return static_cast<float>(width) / static_cast<float>(height);
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
  switch (mode) {
    case CursorMode::CAPTURED:
      glfwSetInputMode(window.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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

}