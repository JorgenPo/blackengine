//
// Created by popof on 02.10.2018.
//

#include "GLFWWindow.h"
#include <util/Input.h>

namespace black {

GLFWWindow::GLFWWindow(const std::string &title, int width, int height, bool isFullScreen)
    : AbstractRenderWindow(title, width, height, isFullScreen), window(nullptr, nullptr), isWindowShown(false),
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

}