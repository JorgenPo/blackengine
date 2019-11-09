//
// Created by popov on 07.07.2019.
//

#ifndef BLACKENGINE_APPLICATIONSHADER_H
#define BLACKENGINE_APPLICATIONSHADER_H

#include "ShaderProgram.h"
#include "../Camera.h"
#include "../components/LightComponent.h"
#include <BlackEngine/render/Material.h>

#include <glm/glm.hpp>
#include <memory>

namespace black {

/**
 * High level shader based on ShaderProgram abstraction
 */
class ApplicationShader {
protected:
  std::shared_ptr<ShaderProgram> impl;
  std::shared_ptr<Camera> camera;
  std::shared_ptr<LightComponent> directedLight;
  glm::mat4 model{};
  Color ambientLightColor = Color::WHITE;
  float ambientLightIntensity = 0.1f;
  glm::vec3 directedLightPosition{};
  Material material;

public:
  explicit ApplicationShader(std::shared_ptr<ShaderProgram> impl);
  explicit ApplicationShader(const std::shared_ptr<ApplicationShader>& shader);

  virtual ~ApplicationShader();

  void use();

  void setCamera(const std::shared_ptr<Camera> &camera);
  void setModelMatrix(const glm::mat4 &model);
  void setMaterial(const Material &material);

  void setDirectedLight(const glm::vec3 &position, const std::shared_ptr<LightComponent> &light);
  void setAmbientLight(Color color, float intensity);

  Color getAmbientLightColor() const;
private:
  virtual void setCameraImpl(const std::shared_ptr<Camera> &camera) = 0;
  virtual void setModelMatrixImpl(const glm::mat4 &model) = 0;
  virtual void setAmbientLightImpl(Color color, float intensity) = 0;
  virtual void setLightImpl(const glm::vec3 &position, const std::shared_ptr<LightComponent> &light) = 0;
  virtual void setMaterialImpl(const Material &material) = 0;

};

}


#endif //BLACKENGINE_APPLICATIONSHADER_H
