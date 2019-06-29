//
// Created by popof on 29.09.2018.
//

#include "OpenGLRenderSystem.h"
#include "GLFWWindow.h"

#include "GLMesh.h"
#include "GLTexture.h"
#include "GLRenderer.h"
#include "GLSLShader.h"
#include "GLSLShaderProgram.h"

#include <log/Logger.h>

namespace black {

OpenGLRenderSystem::OpenGLRenderSystem() {
  this->logger = Logger::Get("OpenGLRenderSystem");
}

std::string OpenGLRenderSystem::getName() const {
  return std::string("OpenGL");
}

void OpenGLRenderSystem::initialize(std::string title, int width, int height, bool isFullScreen) {
  this->logger->trace("Initialization");

  this->logger->info("Using OpenGL 3.3 Core profile");

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef BLACK_PLATFORM_MACOSX
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  this->window = std::make_shared<GLFWWindow>(std::move(title), width, height, isFullScreen);
  this->window->setRenderTargetCurrent();

  // Init GLAD
  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    this->logger->critical("Failed to init OpenGL Context");
    glfwTerminate();
    throw RenderSystemInitializationException("Failed to initialize OpenGL Context");
  }

  this->renderer = std::make_shared<GLRenderer>();
}

void OpenGLRenderSystem::shutdown() {
  this->logger->trace("Shutdown");

  glfwTerminate();
}

std::shared_ptr<RendererInterface> OpenGLRenderSystem::getRenderer() {
  return this->renderer;
}

OpenGLRenderSystem::~OpenGLRenderSystem() {
  this->logger->trace("Destructor!");
}

std::shared_ptr<AbstractRenderWindow> OpenGLRenderSystem::getRenderWindow() {
  return this->window;
}

std::shared_ptr<Mesh> OpenGLRenderSystem::createMesh(
    std::vector<float> vertices, std::vector<float> textureCoords) {
  return std::make_shared<GLMesh>(vertices, textureCoords);
}

std::shared_ptr<Shader> OpenGLRenderSystem::createShader(std::string source, Shader::Type type) {
  return std::make_shared<GLSLShader>(std::move(source), type);
}

std::shared_ptr<ShaderProgram> OpenGLRenderSystem::createShaderProgram(std::shared_ptr<Shader> vertexShader,
                                                                       std::shared_ptr<Shader> fragmentShader) {
  return std::make_shared<GLSLShaderProgram>(std::move(vertexShader), std::move(fragmentShader));
}

std::string OpenGLRenderSystem::getErrorString(GLenum error) {
  // TODO: make switch
  return std::string(std::to_string(error));
}

std::shared_ptr<Texture>
OpenGLRenderSystem::createTexture(const std::shared_ptr<Image> &image, bool generateMipMaps,
                                  TextureFiltering filtering, TextureWrapping wrapping) {
  return std::make_shared<GLTexture>(image, generateMipMaps, filtering, wrapping);
}

std::shared_ptr<SystemInterface> OpenGLRenderSystem::getSystemInterface() {
  return this->window;
}
}