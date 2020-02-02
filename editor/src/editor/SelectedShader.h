//
// Created by popov on 07.07.2019.
//

#ifndef BLACKENGINE_SELECTEDSHADER_H
#define BLACKENGINE_SELECTEDSHADER_H

#include <BlackEngine/shader/ApplicationShader.h>

using namespace black;

namespace blackeditor {
class SelectedShader : public ApplicationShader {
public:
  explicit SelectedShader(const std::shared_ptr<ShaderProgram> &impl);
  explicit SelectedShader(const std::shared_ptr<ApplicationShader>& shader);

  void setCameraImpl(const std::shared_ptr<Camera> &camera) override;

  void setModelMatrixImpl(const glm::mat4 &model) override;

  void setAmbientLightImpl(const AmbientLight &light) override;

  void setColor(Color color, float intensity);

private:
  void setDirectedLightImpl(const std::shared_ptr<DirectedLight> &light) override;

  void setPointLightImpl(const std::shared_ptr<PointLight> &light) override;

public:

  void setMaterialImpl(const Material &material) override;
};

}

#endif //BLACKENGINE_SELECTEDSHADER_H
