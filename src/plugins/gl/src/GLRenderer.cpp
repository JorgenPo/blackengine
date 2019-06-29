//
// Created by popof on 09.10.2018.
//

#include "GLRenderer.h"
#include "GLSLShader.h"
#include "GLSLShaderProgram.h"

#include "OpenGLRenderSystem.h"

#include <GameEntity.h>
#include <Camera.h>

#include <render/Mesh.h>
#include <render/Material.h>
#include <components/ModelComponent.h>
#include <components/TransformComponent.h>
#include <util/FileSystem.h>

#include <log/Logger.h>
#include <util/ShaderManager.h>

namespace black {

void GLRenderer::setCurrentRenderTarget(std::shared_ptr<RenderTargetInterface> target) {
  this->currentTarget = target;
}

void GLRenderer::render(std::shared_ptr<GameEntity> object, std::shared_ptr<Camera> camera) {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  auto lastError = glGetError();

  if (lastError != GL_NO_ERROR) {
    this->logger->critical("OpenGL error: {0}", OpenGLRenderSystem::getErrorString(lastError));
  }

  // Make the diffuse shader current
  this->diffuseShader->use();

  this->diffuseShader->setUniformVariable("model", object->transform->getModelMatrix());
  this->diffuseShader->setUniformVariable("view", camera->getViewMatrix());
  this->diffuseShader->setUniformVariable("projection", camera->getProjectionMatrix());

  auto modelComponent = object->get<ModelComponent>();
  if (modelComponent == nullptr) {
    return;
  }

  for (const auto &part : modelComponent->getParts()) {
    part.mesh->bind();

    if (part.material->texture != nullptr) {
      part.material->texture->bind();
    }

    glDrawArrays(static_cast<GLenum>(part.mesh->getDrawMode()), 0, static_cast<GLsizei>(part.mesh->getVerticesCount()));

    if (part.material->texture != nullptr) {
      part.material->texture->unbind();
    }
  }
}

void GLRenderer::setViewPort(int x, int y, int width, int height) {
  glViewport(x, y, width, height);
}

GLRenderer::GLRenderer()
    : currentTarget(), model(1.0f) {

  this->logger = Logger::Get("GLRenderer");

  try {
    createShaders();
  } catch (const Exception &e) {
    logger->critical("Failed to create shader programs: " + e.getMessage());
    throw RendererInitializationException("Failed to create shader program: " + e.getMessage());
  }

  glEnable(GL_CULL_FACE);
  glCullFace(GL_CW);
}

void GLRenderer::createShaders() {
  this->diffuseShader = util::ShaderManager::CreateShaderProgramFromFile(
      "shaders/simple_vertex.glsl", "shaders/simple_fragment.glsl");

  glEnable(GL_DEPTH_TEST);
}
}