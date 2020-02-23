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
class SimpleShader : public ApplicationShader {
public:
  explicit SimpleShader(const std::shared_ptr<ShaderProgram> &impl);
  using ApplicationShader::ApplicationShader;

  void setCameraImpl(const std::shared_ptr<Camera> &camera) override;

  void setModelMatrixImpl(const glm::mat4 &model) override;

  void setAmbientLightImpl(const AmbientLight &light) override;

private:
  void setDirectedLightImpl(const std::shared_ptr<DirectedLight> &light) override;

  void setPointLightImpl(const std::shared_ptr<PointLight> &light) override;

public:

  void setMaterialImpl(const Material &material) override;
};

}

#endif //BLACKENGINE_SIMPLESHADER_H
