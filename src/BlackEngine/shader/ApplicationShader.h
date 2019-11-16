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

class Light;

/**
 * High level shader based on ShaderProgram abstraction
 */
class ApplicationShader {
protected:
  std::shared_ptr<ShaderProgram> impl;
  std::shared_ptr<Camera> camera;
  std::shared_ptr<Light> directedLight;
  glm::mat4 model{};
  Color ambientLightColor = Color::WHITE;
  float ambientLightIntensity = 0.1f;
  Material material;

public:
  explicit ApplicationShader(std::shared_ptr<ShaderProgram> impl);
  explicit ApplicationShader(const std::shared_ptr<ApplicationShader>& shader);

  virtual ~ApplicationShader();

  void use();

  void setCamera(const std::shared_ptr<Camera> &camera);
  void setModelMatrix(const glm::mat4 &model);
  void setMaterial(const Material &material);

  void setDirectedLight(std::shared_ptr<Light> light);
  void setAmbientLight(Color color, float intensity);

  Color getAmbientLightColor() const;
private:
  virtual void setCameraImpl(const std::shared_ptr<Camera> &camera) = 0;
  virtual void setModelMatrixImpl(const glm::mat4 &model) = 0;
  virtual void setAmbientLightImpl(Color color, float intensity) = 0;
  virtual void setLightImpl(const std::shared_ptr<Light> &light) = 0;
  virtual void setMaterialImpl(const Material &material) = 0;

};

}


#endif //BLACKENGINE_APPLICATIONSHADER_H
