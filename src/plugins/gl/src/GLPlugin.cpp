//
// Created by popof on 27.09.2018.
//

#include <Engine.h>

#include "glfw/GLFWSystemInterface.h"
#include "GLPlugin.h"
#include "OpenGLRenderSystem.h"

#include <log/Logger.h>

namespace black {

std::shared_ptr<Logger> GLPlugin::logger;

std::string GLPlugin::getName() {
  return std::string("GLPlugin");
}

void GLPlugin::install() {
  auto renderSystem = std::make_shared<OpenGLRenderSystem>();
  Engine::RegisterRenderSystem(std::move(renderSystem));

  auto systemInterface = std::make_shared<GLFWSystemInterface>();
  Engine::RegisterSystemInterface(std::move(systemInterface));
}

void GLPlugin::initialize() {
}

void GLPlugin::shutdown() {
}

void GLPlugin::uninstall() {
}

GLPlugin::GLPlugin() {
  logger = Logger::Get("GLPlugin");
}
}