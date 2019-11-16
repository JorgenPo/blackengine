//
// Created by popof on 09.10.2018.
//

#ifndef BLACKENGINE_GLRENDERER_H
#define BLACKENGINE_GLRENDERER_H

#include <BlackEngine/common/CommonHeaders.h>
#include <BlackEngine/render/RendererInterface.h>

#include "OpenGLCommonHeaders.h"

#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include <unordered_map>

namespace black {
class ApplicationShader;
class Logger;
class ModelPart;
class DirectionLight;

/**
 * OpenGL v4.0 Renderer
 */
class GLRenderer : public RendererInterface {
  std::shared_ptr<RenderTargetInterface> currentTarget;
  std::shared_ptr<ApplicationShader> defaultShader;
  std::shared_ptr<ApplicationShader> currentShader;
  std::shared_ptr<DirectionLight> currentLight;
  std::shared_ptr<Logger> logger;

  glm::mat4 model;

  int lastError = 0;

public:
  GLRenderer();

  void setCurrentRenderTarget(std::shared_ptr<RenderTargetInterface> target) override;

  std::shared_ptr<RenderTargetInterface> getCurrentRenderTarget() const noexcept override;

  void render(const std::shared_ptr<AbstractScene> &scene) override;

  void setViewPort(int x, int y, int width, int height) override;

private:
  void renderObject(const std::shared_ptr<GameObject> &object, const std::shared_ptr<Camera> &camera);
  void renderPart(const ModelPart &part) const;
  void createShaders();
};

}

#endif //BLACKENGINE_GLRENDERER_H
