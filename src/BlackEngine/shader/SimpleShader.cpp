//
// Created by popov on 07.07.2019.
//

#include "SimpleShader.h"
#include "ShaderProgram.h"

#include "../Camera.h"

#include <BlackEngine/components/TransformComponent.h>
#include <BlackEngine/components/LightComponent.h>
#include <BlackEngine/render/Material.h>

namespace black {

SimpleShader::SimpleShader(const std::shared_ptr<ShaderProgram> &impl) : ApplicationShader(impl) {}

void SimpleShader::setCameraImpl(const std::shared_ptr<Camera> &camera) {
  this->impl->setUniformVariable("view", camera->getViewMatrix());
  this->impl->setUniformVariable("projection", camera->getProjectionMatrix());
  this->impl->setUniformVariable("cameraPosition", camera->getPosition());
}

void SimpleShader::setModelMatrixImpl(const glm::mat4 &model) {
  this->impl->setUniformVariable("model", model);
}

void SimpleShader::setAmbientLightImpl(const AmbientLight &light) {
  this->impl->setUniformVariable("ambientLight.intensity", light.intensity);
  this->impl->setUniformVariable("ambientLight.color", light.color.getRgb());
}

void SimpleShader::setMaterialImpl(const Material &material) {
  this->impl->setUniformVariable("material.color", material.color.getRgb());
  this->impl->setUniformVariable("material.spectacularFactor", material.spectacularFactor);
}

void SimpleShader::setDirectedLightImpl(const std::shared_ptr<DirectedLight> &light) {
  this->impl->setUniformVariable("light.enabled", light != nullptr);

  if (light) {
    this->impl->setUniformVariable("light.direction", light->getDirection());
    this->impl->setUniformVariable("light.color", light->getColor().getRgb());
    this->impl->setUniformVariable("light.diffuseIntensity", light->getIntensity());
    this->impl->setUniformVariable("light.spectacularIntensity", light->getSpectacularIntensity());
  }
}

void SimpleShader::setPointLightImpl(const std::shared_ptr<PointLight> &light) {
  this->impl->setUniformVariable("light.enabled", light != nullptr);

  if (light) {
    this->impl->setUniformVariable("light.position", light->getPosition());
    this->impl->setUniformVariable("light.color", light->getColor().getRgb());
    this->impl->setUniformVariable("light.diffuseIntensity", light->getIntensity());
    this->impl->setUniformVariable("light.spectacularIntensity", light->getSpectacularIntensity());
  }
}
}