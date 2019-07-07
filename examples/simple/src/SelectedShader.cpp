//
// Created by popov on 07.07.2019.
//

#include "SelectedShader.h"

SelectedShader::SelectedShader(const std::shared_ptr<ShaderProgram> &impl) : ApplicationShader(impl) {}

void SelectedShader::setCamera(const std::shared_ptr<Camera> &camera) {
  this->impl->setUniformVariable("view", camera->getViewMatrix());
  this->impl->setUniformVariable("projection", camera->getProjectionMatrix());
}

void SelectedShader::setModelMatrix(const glm::mat4 &model) {
  this->impl->setUniformVariable("model", model);
}

void SelectedShader::setAmbientLight(const glm::vec3 &color, float intensity) {
}

void SelectedShader::setLight(const glm::vec3 &position, const std::shared_ptr<LightComponent> &light) {
}

void SelectedShader::setMaterial(const black::Material &material) {
  this->impl->setUniformVariable("material.color", material.color.getRgb());
}
