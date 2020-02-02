//
// Created by popov on 07.07.2019.
//

#include "SelectedShader.h"
#include <BlackEngine/log/Logger.h>

using namespace blackeditor;

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

void SelectedShader::setMaterialImpl(const black::Material &material) {
  this->impl->setUniformVariable("material.color", material.color.getRgb());
}

SelectedShader::SelectedShader(const std::shared_ptr<ApplicationShader>& shader) : ApplicationShader(shader) {

}

void SelectedShader::setColor(Color color, float intensity) {
  this->impl->setUniformVariable("color.rgb", color.getRgb());
  this->impl->setUniformVariable("color.intensity", intensity);
}

void SelectedShader::setDirectedLightImpl(const std::shared_ptr<DirectedLight> &light) {

}

void SelectedShader::setPointLightImpl(const std::shared_ptr<PointLight> &light) {

}
