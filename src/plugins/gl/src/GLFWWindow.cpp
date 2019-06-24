//
// Created by popof on 02.10.2018.
//

#include "GLFWWindow.h"

namespace black {

GLFWWindow::GLFWWindow(const std::string &title, int width, int height, bool isFullScreen)
    : AbstractRenderWindow(title, width, height, isFullScreen), window(nullptr, nullptr), isWindowShown(false) {

  // Init GLFW window
  auto glfwWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

  if (glfwWindow == nullptr) {
    throw RenderWindowInitializationException("Failed to initialize glfw window");
  }

  this->window = std::unique_ptr<GLFWwindow, void (*)(GLFWwindow *)>(glfwWindow, glfwDestroyWindow);

  glfwSetFramebufferSizeCallback(this->window.get(), [](GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
  });
}

void GLFWWindow::updateRenderTarget() {
  glfwSwapBuffers(this->window.get());
}

void GLFWWindow::setRenderTargetCurrent() {
  glfwMakeContextCurrent(this->window.get());
}

float GLFWWindow::getRenderTargetWidth() {
  return width;
}

float GLFWWindow::getRenderTargetHeight() {
  return height;
}

float GLFWWindow::getRenderTargetAspectRatio() {
  return width / static_cast<float>(height);
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
}