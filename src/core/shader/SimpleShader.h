//
// Created by popov on 07.07.2019.
//

#ifndef BLACKENGINE_SIMPLESHADER_H
#define BLACKENGINE_SIMPLESHADER_H

#include "ApplicationShader.h"

namespace black {

/**
 * Default simple shader with phong light and material
 */
class SimpleShader final : public ApplicationShader {
public:
  explicit SimpleShader(const std::shared_ptr<ShaderProgram> &impl);

  void setCamera(const std::shared_ptr<Camera> &camera) override;

  void setModelMatrix(const glm::mat4 &model) override;

  void setAmbientLight(const glm::vec3 &color, float intensity) override;

  void setLight(const glm::vec3 &position, const std::shared_ptr<LightComponent> &light) override;

  void setMaterial(const Material &material) override;
};

}

#endif //BLACKENGINE_SIMPLESHADER_H
