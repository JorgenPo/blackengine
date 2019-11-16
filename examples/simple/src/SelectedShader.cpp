//
// Created by popov on 07.07.2019.
//

#include "SelectedShader.h"
#include <BlackEngine/log/Logger.h>

SelectedShader::SelectedShader(const std::shared_ptr<ShaderProgram> &impl) : ApplicationShader(impl) {}

void SelectedShader::setCameraImpl(const std::shared_ptr<Camera> &camera) {
  this->impl->setUniformVariable("view", camera->getViewMatrix());
  this->impl->setUniformVariable("projection", camera->getProjectionMatrix());
}

void SelectedShader::setModelMatrixImpl(const glm::mat4 &model) {
  this->impl->setUniformVariable("model", model);
}

void SelectedShader::setAmbientLightImpl(const AmbientLight &light) {

}

void SelectedShader::setLightImpl(const std::shared_ptr<DirectionLight> &light) {
}

void SelectedShader::setMaterialImpl(const black::Material &material) {
  this->impl->setUniformVariable("material.color", material.color.getRgb());
}

SelectedShader::SelectedShader(std::shared_ptr<ApplicationShader> shader) : ApplicationShader(std::move(shader)) {

}

void SelectedShader::setColor(Color color, float intensity) {
  this->impl->setUniformVariable("color.rgb", color.getRgb());
  this->impl->setUniformVariable("color.intensity", intensity);
}
