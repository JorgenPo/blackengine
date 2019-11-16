#ifndef BLACKENGINE_SRC_CORE_UTIL_SHADERMANAGER_H
#define BLACKENGINE_SRC_CORE_UTIL_SHADERMANAGER_H

#include "../common/Exported.h"
#include <BlackEngine/shader/Shader.h>

#include <memory>

namespace black {

class ShaderProgram;

namespace util {

class BLACK_EXPORTED ShaderManager {
public:
  /**
   * Load shader from file and try to compile it.
   *
   * @param fileName Shader file name
   * @param type Type of the shader
   * @return Compiled shader
   */
  static std::shared_ptr<Shader> CreateShaderFromFile(std::string_view fileName, Shader::Type type);

  /**
   * Load fragment and vertex shaders from files, compile it and
   * link into shader program.
   *
   * @param vertexShaderFile File with a vertex shader
   * @param fragmentShaderFile File with a fragment shader
   * @return Linked and ready to use program
   */
  static std::shared_ptr<ShaderProgram> CreateShaderProgramFromFile(
      std::string_view vertexShaderFile, std::string_view fragmentShaderFile);

  template<typename ShaderClass>
  static std::shared_ptr<ShaderClass> CreateApplicationShaderFromFile(
    std::string_view vertexShaderFile, std::string_view fragmentShaderFile);
};

template<typename ShaderClass>
std::shared_ptr<ShaderClass>
ShaderManager::CreateApplicationShaderFromFile(std::string_view vertexShaderFile, std::string_view fragmentShaderFile) {
  auto shaderProgram = CreateShaderProgramFromFile(vertexShaderFile, fragmentShaderFile);
  return std::make_shared<ShaderClass>(shaderProgram);
}

}}

#endif //BLACKENGINE_SRC_CORE_UTIL_SHADERMANAGER_H
