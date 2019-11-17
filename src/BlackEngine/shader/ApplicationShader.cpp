//
// Created by popov on 07.07.2019.
//

#include "ApplicationShader.h"
#include "ShaderProgram.h"

#include <BlackEngine/components/LightComponent.h>
#include <BlackEngine/log/Logger.h>

namespace black {

ApplicationShader::~ApplicationShader() = default;

ApplicationShader::ApplicationShader(std::shared_ptr<ShaderProgram> impl)
  : impl(std::move(impl)) {

}

void ApplicationShader::use() {
  impl->use();

  if (camera) {
    setCameraImpl(camera);
  }

  setModelMatrixImpl(model);
  setMaterialImpl(material);
}

ApplicationShader::ApplicationShader(const std::shared_ptr<ApplicationShader>& shader) {
  this->impl = shader->impl->copy();
  this->impl->link();
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

void ApplicationShader::setLight(const std::shared_ptr<LightComponent>& light) {
  switch (light->getType()) {
    case LightType::DIRECTED:
      setDirectedLightImpl(std::dynamic_pointer_cast<DirectedLight>(light));
      break;
    case LightType::SPOT:
      Logger::Get("ApplicationShader")->critical("Spot light is NOT IMPLEMENTED");
      break;
    case LightType::POINT:
      setPointLightImpl(std::dynamic_pointer_cast<PointLight>(light));
      break;
  }
}

void ApplicationShader::setAmbientLight(const AmbientLight &light) {
  setAmbientLightImpl(light);
}

}
