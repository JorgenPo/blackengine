#ifndef BLACKENGINE_GLSLSHADER_H
#define BLACKENGINE_GLSLSHADER_H

#include "OpenGLCommonHeaders.h"
#include <BlackEngine/shader/Shader.h>

namespace black {
class GLSLShader : public Shader {
  static size_t ERROR_BUFFER_LENGTH;
  GLuint shader;

public:
  /**
   * Very simple vertex shader code
   */
  static constexpr auto SimpleVertex =
      "#version 330 core\n"
      "layout (location = 0) in vec3 pos;\n"
      "layout (location = 1) in vec2 texCoord;\n"
      "\n"
      "uniform mat4 projection;\n"
      "uniform mat4 view;\n"
      "uniform mat4 model;\n"
      "\n"
      "out vec2 TexCoord;\n"
      "\n"
      "void main()\n"
      "{\n"
      "    gl_Position = projection * view * model * vec4(pos, 1.0);\n"
      "    TexCoord = texCoord;\n"
      "}";

  /**
   * Very simple fragment shader code
   */
  static constexpr auto SimpleFragment =
      "#version 330 core\n"
      "out vec4 FragColor;\n"
      "\n"
      "in vec2 TexCoord;\n"
      "\n"
      "uniform sampler2D diffuse;\n"
      "void main()\n"
      "{\n"
      "    FragColor = texture(diffuse, TexCoord);\n"
      "} ";

public:
  GLSLShader(const std::string &code, Type type);

  virtual ~GLSLShader();

  void compile() override;

  void *getImplementation() override;

private:
  static GLenum ToGLShaderType(Type type);
  bool isCompiledSuccessfully();
  std::string getCompilationError();
};
}

#endif //BLACKENGINE_GLSLSHADER_H
