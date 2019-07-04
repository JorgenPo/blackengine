//
// Created by popof on 09.10.2018.
//

#ifndef BLACKENGINE_GLRENDERER_H
#define BLACKENGINE_GLRENDERER_H

#include <CommonHeaders.h>
#include <render/RendererInterface.h>

#include "OpenGLCommonHeaders.h"

#include <glm/glm.hpp>
#include <memory>
#include <vector>

namespace black {
class ShaderProgram;
class Logger;
class ModelPart;

/**
 * OpenGL v4.0 Renderer
 */
class GLRenderer : public RendererInterface {
  std::shared_ptr<RenderTargetInterface> currentTarget;
  std::shared_ptr<ShaderProgram> diffuseShader;
  std::shared_ptr<Logger> logger;

  glm::mat4 model;

public:
  GLRenderer();

  void setCurrentRenderTarget(std::shared_ptr<RenderTargetInterface> target) override;

  void render(
      const std::vector<std::shared_ptr<GameEntity>> &objects,
      const std::shared_ptr<Camera> &camera) override;

  void setViewPort(int x, int y, int width, int height) override;

private:
  void renderObject(const std::shared_ptr<GameEntity> &object) const;
  void renderPart(const ModelPart &part) const;
  void createShaders();
};

}

#endif //BLACKENGINE_GLRENDERER_H
