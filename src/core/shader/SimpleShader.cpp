//
// Created by popov on 07.07.2019.
//

#include "SimpleShader.h"
#include "ShaderProgram.h"

#include <Camera.h>

#include <components/LightComponent.h>
#include <render/Material.h>

namespace black {

SimpleShader::SimpleShader(const std::shared_ptr<ShaderProgram> &impl) : ApplicationShader(impl) {}

void SimpleShader::setCamera(const std::shared_ptr<Camera> &camera) {
  this->impl->setUniformVariable("view", camera->getViewMatrix());
  this->impl->setUniformVariable("projection", camera->getProjectionMatrix());
  this->impl->setUniformVariable("cameraPosition", camera->getPosition());
}

void SimpleShader::setModelMatrix(const glm::mat4 &model) {
  this->impl->setUniformVariable("model", model);
}

void SimpleShader::setAmbientLight(const glm::vec3 &color, float intensity) {
  this->impl->setUniformVariable("ambientLight.intensity", intensity);
  this->impl->setUniformVariable("ambientLight.color", color);
}

void SimpleShader::setLight(const glm::vec3 &position, const std::shared_ptr<LightComponent> &light) {
  this->impl->setUniformVariable("light.position", position);
  this->impl->setUniformVariable("light.color", light->getColor().getRgb());
  this->impl->setUniformVariable("light.diffuseIntensity", light->getIntensity());
  this->impl->setUniformVariable("light.spectacularIntensity", light->getSpectacularIntensity());
}

void SimpleShader::setMaterial(const Material &material) {
  this->impl->setUniformVariable("material.color", material.color.getRgb());
  this->impl->setUniformVariable("material.spectacularFactor", material.spectacularFactor);
}
}