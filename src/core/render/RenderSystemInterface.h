//
// Created by popof on 29.09.2018.
//

#ifndef BLACKENGINE_RENDERSYSTEMINTERFACE_H
#define BLACKENGINE_RENDERSYSTEMINTERFACE_H

#include "Texture.h"

#include <shader/Shader.h>

#include <CommonHeaders.h>

#include <vector>

namespace black {

class RendererInterface;
class AbstractRenderWindow;
class SystemInterface;
class Mesh;
class Shader;
class ShaderProgram;

class RenderSystemInitializationException : public Exception {
public:
  explicit RenderSystemInitializationException(const std::string &message) : Exception(message) {
  }
};

class RenderSystemInterface {
public:
  /**
   * Return an unique render system name.
   *
   * @return Name of the render system.
   */
  [[nodiscard]] virtual std::string getName() const = 0;

  /**
   * Initialize a render system.
   * Also will initialize the renderer and main render window.
   *
   * @throws RenderSystemInitializationException
   */
  virtual void initialize(std::string title, int width, int height, bool isFullScreen) = 0;

  /**
   * Shutdown a render system.
   */
  virtual void shutdown() = 0;

  /**
   * Create an appropriate render system render and render window.
   *
   * @return Renderer for this render system
   */
  virtual std::shared_ptr<RendererInterface> getRenderer() = 0;

  /**
   * Return a main renderer window
   *
   * @return Pointer for the renderer window
   */
  virtual std::shared_ptr<AbstractRenderWindow> getRenderWindow() = 0;

  /**
   * Return a pointer to the System Interface
   * @return System interface pointer
   */
  virtual std::shared_ptr<SystemInterface> getSystemInterface() = 0;

  /**
   * Create a mesh
   *
   * @return Pointer to the created mesh
   */
  virtual std::shared_ptr<Mesh> createMesh(std::vector<float> vertices, std::vector<float> textureCoords) = 0;

  virtual std::shared_ptr<Shader> createShader(std::string source, Shader::Type type) = 0;
  virtual std::shared_ptr<ShaderProgram> createShaderProgram(std::shared_ptr<Shader> vertexShader,
                                                             std::shared_ptr<Shader> fragmentShader) = 0;

  virtual std::shared_ptr<Texture> createTexture(const std::shared_ptr<Image> &image, bool generateMipMaps,
                                                 TextureFiltering filtering,
                                                 TextureWrapping wrapping) = 0;
};
}

#endif //BLACKENGINE_RENDERSYSTEMINTERFACE_H
