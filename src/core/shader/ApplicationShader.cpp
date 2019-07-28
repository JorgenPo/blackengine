//
// Created by popov on 07.07.2019.
//

#include "ApplicationShader.h"
#include "ShaderProgram.h"

namespace black {

ApplicationShader::~ApplicationShader() = default;

ApplicationShader::ApplicationShader(std::shared_ptr<ShaderProgram> impl)
  : impl(std::move(impl)), ambientLightColor(Color::WHITE) {

}

void ApplicationShader::use() {
  impl->use();

  if (camera) {
    setCameraImpl(camera);
  }

  if (directedLight) {
    setLightImpl(directedLightPosition, directedLight);
  }

  setModelMatrixImpl(model);
  setAmbientLightImpl(ambientLightColor, ambientLightIntensity);
  setMaterialImpl(material);
}

ApplicationShader::ApplicationShader(const std::shared_ptr<ApplicationShader>& shader) {
  this->impl = shader->impl;
}

void ApplicationShader::setCamera(const std::shared_ptr<Camera> &newCamera) {
  camera = newCamera;
  setCameraImpl(camera);
}

void ApplicationShader::setModelMatrix(const glm::mat4 &newModel) {
  model = newModel;
  setModelMatrixImpl(model);
}

void ApplicationShader::setMaterial(const Material &newMaterial) {
  material = newMaterial;
  setMaterialImpl(newMaterial);
}

void ApplicationShader::setDirectedLight(const glm::vec3 &position, const std::shared_ptr<LightComponent> &light) {
  directedLightPosition = position;
  directedLight = light;
  setLightImpl(directedLightPosition, directedLight);
}

void ApplicationShader::setAmbientLight(Color color, float intensity) {
  ambientLightIntensity = intensity;
  ambientLightColor = color;
  setAmbientLightImpl(ambientLightColor, ambientLightIntensity);
}

Color ApplicationShader::getAmbientLightColor() const {
  return ambientLightColor;
}

}
