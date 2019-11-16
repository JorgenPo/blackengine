//
// Created by popof on 09.10.2018.
//

#include "GLRenderer.h"
#include "GLSLShader.h"

#include "OpenGLRenderSystem.h"

#include <BlackEngine/GameObject.h>
#include <BlackEngine/Camera.h>
#include <BlackEngine/Light.h>

#include <BlackEngine/render/Mesh.h>
#include <BlackEngine/render/Material.h>
#include <BlackEngine/components/ModelComponent.h>
#include <BlackEngine/components/TransformComponent.h>

#include <BlackEngine/shader/SimpleShader.h>
#include <BlackEngine/scene/AbstractScene.h>
#include <BlackEngine/render/RenderTargetInterface.h>

#include <BlackEngine/log/Logger.h>
#include <BlackEngine/util/ShaderManager.h>
#include <BlackEngine/util/FileSystem.h>


namespace black {

void GLRenderer::setCurrentRenderTarget(std::shared_ptr<RenderTargetInterface> target) {
  this->currentTarget = target;
}

void GLRenderer::render(const std::shared_ptr<AbstractScene> &scene) {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  lastError = glGetError();

  if (lastError != GL_NO_ERROR) {
    this->logger->critical("OpenGL error: {0}", OpenGLRenderSystem::getErrorString(lastError));
  }

  this->defaultShader->use();
  this->defaultShader->setCamera(scene->getCurrentCamera());
  this->defaultShader->setAmbientLight(Color::WHITE, 0.2f);

  currentLight = scene->getLight();

  for (auto && object : scene->getObjects()) {
    this->currentShader = defaultShader;
    this->currentShader->use();
    renderObject(object, scene->getCurrentCamera());
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
  glCullFace(GL_BACK);
}

void GLRenderer::createShaders() {
  this->defaultShader = util::ShaderManager::CreateApplicationShaderFromFile<SimpleShader>(
      "resources/simple_vertex.glsl", "resources/simple_fragment.glsl");
  this->defaultShader->use();

  glEnable(GL_DEPTH_TEST);
}

void GLRenderer::renderObject(const std::shared_ptr<GameObject> &object, const std::shared_ptr<Camera> &camera)  {
  auto modelComponent = object->get<ModelComponent>();

  if (modelComponent != nullptr) {
    if (const auto &shader = object->get<ModelComponent>()->getShader(); shader != nullptr) {
      this->currentShader = shader;
      this->currentShader->use();
      this->currentShader->setCamera(camera);
    }
  }

  if (!modelComponent) {
    return;
  }

  this->currentShader->setModelMatrix(object->transform->getModelMatrix());
  this->currentShader->setDirectedLight(this->currentLight);

  for (const auto &part : modelComponent->getParts()) {
    renderPart(part);
  }
}

void GLRenderer::renderPart(const ModelPart &part) const {
  part.mesh->bind();

  if (part.material.texture != nullptr) {
    part.material.texture->bind();
  }

  this->currentShader->setMaterial(part.material);

  glDrawArrays(static_cast<GLenum>(part.mesh->getDrawMode()), 0, static_cast<GLsizei>(part.mesh->getVerticesCount()));

  if (part.material.texture != nullptr) {
    part.material.texture->unbind();
  }
}

std::shared_ptr<RenderTargetInterface> GLRenderer::getCurrentRenderTarget() const noexcept {
  return currentTarget;
}

}