//
// Created by popov on 07.07.2019.
//

#ifndef BLACKENGINE_APPLICATIONSHADER_H
#define BLACKENGINE_APPLICATIONSHADER_H

#include "ShaderProgram.h"
#include <Camera.h>
#include <components/LightComponent.h>
#include <render/Material.h>

#include <glm/glm.hpp>
#include <memory>

namespace black {

/**
 * High level shader based on ShaderProgram abstraction
 */
class ApplicationShader {
protected:
  std::shared_ptr<ShaderProgram> impl;

public:
  explicit ApplicationShader(std::shared_ptr<ShaderProgram> impl);
  virtual ~ApplicationShader();

  virtual void setCamera(const std::shared_ptr<Camera> &camera) = 0;
  virtual void setModelMatrix(const glm::mat4 &model) = 0;
  virtual void setAmbientLight(const glm::vec3 &color, float intensity) = 0;
  virtual void setLight(const glm::vec3 &position, const std::shared_ptr<LightComponent> &light) = 0;
  virtual void setMaterial(const Material &material) = 0;

  void use();
};

}


#endif //BLACKENGINE_APPLICATIONSHADER_H
