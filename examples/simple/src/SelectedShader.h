//
// Created by popov on 07.07.2019.
//

#ifndef BLACKENGINE_SELECTEDSHADER_H
#define BLACKENGINE_SELECTEDSHADER_H

#include <BlackEngine/shader/ApplicationShader.h>

using namespace black;

class SelectedShader : public ApplicationShader {
public:
  explicit SelectedShader(const std::shared_ptr<ShaderProgram> &impl);
  SelectedShader(std::shared_ptr<ApplicationShader> shader);

  void setCameraImpl(const std::shared_ptr<Camera> &camera) override;

  void setModelMatrixImpl(const glm::mat4 &model) override;

  void setAmbientLightImpl(Color color, float intensity) override;

  void setLightImpl(const std::shared_ptr<Light> &light) override;

  void setMaterialImpl(const Material &material) override;
};


#endif //BLACKENGINE_SELECTEDSHADER_H
