//
// Created by popov on 07.07.2019.
//

#include "SelectedShader.h"
#include <log/Logger.h>

SelectedShader::SelectedShader(const std::shared_ptr<ShaderProgram> &impl) : ApplicationShader(impl) {}

void SelectedShader::setCameraImpl(const std::shared_ptr<Camera> &camera) {
  this->impl->setUniformVariable("view", camera->getViewMatrix());
  this->impl->setUniformVariable("projection", camera->getProjectionMatrix());
}

void SelectedShader::setModelMatrixImpl(const glm::mat4 &model) {
  this->impl->setUniformVariable("model", model);
}

void SelectedShader::setAmbientLightImpl(Color color, float intensity) {
  this->impl->setUniformVariable("ambientLight", color.getRgba());
}

void SelectedShader::setLightImpl(const glm::vec3 &position, const std::shared_ptr<LightComponent> &light) {
}

void SelectedShader::setMaterialImpl(const black::Material &material) {
  this->impl->setUniformVariable("material.color", material.color.getRgb());
}

SelectedShader::SelectedShader(std::shared_ptr<ApplicationShader> shader) : ApplicationShader(std::move(shader)) {

}
