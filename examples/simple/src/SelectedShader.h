//
// Created by popov on 07.07.2019.
//

#ifndef BLACKENGINE_SELECTEDSHADER_H
#define BLACKENGINE_SELECTEDSHADER_H

#include <shader/ApplicationShader.h>

using namespace black;

class SelectedShader : public ApplicationShader {
public:
  explicit SelectedShader(const std::shared_ptr<ShaderProgram> &impl);

  void setCamera(const std::shared_ptr<Camera> &camera) override;

  void setModelMatrix(const glm::mat4 &model) override;

  void setAmbientLight(const glm::vec3 &color, float intensity) override;

  void setLight(const glm::vec3 &position, const std::shared_ptr<LightComponent> &light) override;

  void setMaterial(const Material &material) override;
};


#endif //BLACKENGINE_SELECTEDSHADER_H
