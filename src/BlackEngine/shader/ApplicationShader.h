//
// Created by popov on 07.07.2019.
//

#ifndef BLACKENGINE_APPLICATIONSHADER_H
#define BLACKENGINE_APPLICATIONSHADER_H

#include "ShaderProgram.h"
#include "../Camera.h"
#include <BlackEngine/render/Material.h>

#include <glm/glm.hpp>
#include <memory>

namespace black {

class LightComponent;
class PointLight;
class DirectedLight;
class AmbientLight;

/**
 * High level shader based on ShaderProgram abstraction
 */
class ApplicationShader {
protected:
  std::shared_ptr<ShaderProgram> impl;
  std::shared_ptr<Camera> camera;
  glm::mat4 model{};
  Material material;

public:
  explicit ApplicationShader(std::shared_ptr<ShaderProgram> impl);
  explicit ApplicationShader(const std::shared_ptr<ApplicationShader>& shader);

  virtual ~ApplicationShader();

  void use();

  void setCamera(const std::shared_ptr<Camera> &camera);
  void setModelMatrix(const glm::mat4 &model);
  void setMaterial(const Material &material);

  void setLight(const std::shared_ptr<LightComponent>& light);
  void setAmbientLight(const AmbientLight &light);

private:
  virtual void setCameraImpl(const std::shared_ptr<Camera> &camera) = 0;
  virtual void setModelMatrixImpl(const glm::mat4 &model) = 0;
  virtual void setAmbientLightImpl(const AmbientLight &light) = 0;
  virtual void setDirectedLightImpl(const std::shared_ptr<DirectedLight> &light) = 0;
  virtual void setPointLightImpl(const std::shared_ptr<PointLight> &light) = 0;
  virtual void setMaterialImpl(const Material &material) = 0;

};

}


#endif //BLACKENGINE_APPLICATIONSHADER_H
