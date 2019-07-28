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

  void setCameraImpl(const std::shared_ptr<Camera> &camera) override;

  void setModelMatrixImpl(const glm::mat4 &model) override;

  void setAmbientLightImpl(Color color, float intensity) override;

  void setLightImpl(const glm::vec3 &position, const std::shared_ptr<LightComponent> &light) override;

  void setMaterialImpl(const Material &material) override;
};

}

#endif //BLACKENGINE_SIMPLESHADER_H
