#include "GLFWSystemInterface.h"
#include "GLFWWindow.h"

using namespace black;

std::string GLFWSystemInterface::getName() const {
  return "GLFW";
}

SystemInterface::SystemWindow GLFWSystemInterface::createWindow(const WindowData &data) {
  auto window = std::make_shared<GLFWWindow>(data);
  return {window, window}; // renderer window and input system interface at the same time
}
