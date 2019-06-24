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

namespace black {
class GLSLShaderProgram;
class Logger;

/**
 * OpenGL v4.0 Renderer
 */
class GLRenderer : public RendererInterface {
  std::shared_ptr<RenderTargetInterface> currentTarget;
  std::shared_ptr<GLSLShaderProgram> diffuseShader;
  std::shared_ptr<Logger> logger;

  glm::mat4 model;

public:
  GLRenderer();

  void setCurrentRenderTarget(std::shared_ptr<RenderTargetInterface> target) override;

  void render(std::shared_ptr<GameEntity> object, std::shared_ptr<Camera> camera) override;

  void setViewPort(int x, int y, int width, int height) override;

private:
  void createShaders();
};

}

#endif //BLACKENGINE_GLRENDERER_H
