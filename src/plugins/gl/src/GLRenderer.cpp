//
// Created by popof on 09.10.2018.
//

#include "GLRenderer.h"
#include "GLSLShader.h"

#include "OpenGLRenderSystem.h"

#include <GameObject.h>
#include <Camera.h>

#include <render/Mesh.h>
#include <render/Material.h>
#include <components/ModelComponent.h>
#include <components/TransformComponent.h>
#include <components/LightComponent.h>

#include <shader/ApplicationShader.h>
#include <shader/SimpleShader.h>
#include <scene/AbstractScene.h>

#include <log/Logger.h>
#include <util/ShaderManager.h>
#include <util/FileSystem.h>


namespace black {

void GLRenderer::setCurrentRenderTarget(std::shared_ptr<RenderTargetInterface> target) {
  this->currentTarget = target;
}

void GLRenderer::render(const std::vector<std::shared_ptr<GameObject>> &objects,
                        const std::shared_ptr<Camera> &camera, const std::shared_ptr<AbstractScene> &scene) {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  lastError = glGetError();

  if (lastError != GL_NO_ERROR) {
    this->logger->critical("OpenGL error: {0}", OpenGLRenderSystem::getErrorString(lastError));
  }

//  this->defaultShader->use();
//  this->defaultShader->setCamera(camera);
//  this->defaultShader->setAmbientLight(glm::vec3(1.0f, 1.0f, 1.0f), 0.2f);
//
//  for (auto && object : objects) {
//    this->currentShader = defaultShader;
//    this->currentShader->use();
//    renderObject(object, camera);
//  }
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
      "shaders/simple_vertex.glsl", "shaders/simple_fragment.glsl");
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
      this->currentShader->setAmbientLight(glm::vec3(1.0f, 1.0f, 1.0f), 0.2f);
    }
  }

  if (auto light = object->get<LightComponent>(); light != nullptr) {
    this->currentShader->setLight(object->transform->getPosition(), light);
  }

  if (!modelComponent) {
    return;
  }

  this->currentShader->setModelMatrix(object->transform->getModelMatrix());


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

}