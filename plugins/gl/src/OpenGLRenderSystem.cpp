//
// Created by popof on 29.09.2018.
//

#include "OpenGLRenderSystem.h"
#include "glfw/GLFWWindow.h"

#include "GLMesh.h"
#include "GLTexture.h"
#include "GLRenderer.h"
#include "GLSLShader.h"
#include "GLSLShaderProgram.h"

#include <BlackEngine/log/Logger.h>

namespace black {

OpenGLRenderSystem::OpenGLRenderSystem() {
  this->logger = Logger::Get("OpenGLRenderSystem");
}

std::string OpenGLRenderSystem::getName() const {
  return std::string("OpenGL");
}

void OpenGLRenderSystem::initialize() {
  this->logger->trace("Initialization");
}

void OpenGLRenderSystem::shutdown() {
  this->logger->trace("Shutdown");

  glfwTerminate();
}

std::shared_ptr<RendererInterface> OpenGLRenderSystem::createRenderer(
  std::shared_ptr<AbstractRenderWindow> renderWindow) {
  auto renderer = std::make_shared<GLRenderer>();
  renderer->setCurrentRenderTarget(std::move(renderWindow));

  return renderer;
}

OpenGLRenderSystem::~OpenGLRenderSystem() {
  this->logger->trace("Destructor!");
}

std::shared_ptr<Mesh> OpenGLRenderSystem::createMesh(
    std::vector<float> vertices, std::vector<float> textureCoords, std::vector<float> normals) {
  return std::make_shared<GLMesh>(std::move(vertices), std::move(textureCoords), std::move(normals));
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
  switch(error) {
  case GL_INVALID_ENUM:
    return "GL_INVALID_ENUM";
  case GL_NO_ERROR:
    return "GL_NO_ERROR";
  case GL_INVALID_VALUE:
    return "GL_INVALID_VALUE";
  case GL_INVALID_OPERATION:
    return "GL_INVALID_OPERATION";
  case GL_INVALID_FRAMEBUFFER_OPERATION:
    return "GL_INVALID_FRAMEBUFFER_OPERATION";
  case GL_OUT_OF_MEMORY:
    return "GL_OUT_OF_MEMORY";
  default:
    return fmt::format("Unknown error{:x}", error);
  }
}

std::shared_ptr<Texture>
OpenGLRenderSystem::createTexture(const std::shared_ptr<Image> &image, bool generateMipMaps,
                                  TextureFiltering filtering, TextureWrapping wrapping) {
  return std::make_shared<GLTexture>(image, generateMipMaps, filtering, wrapping);
}

}