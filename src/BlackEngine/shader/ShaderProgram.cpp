#include "ShaderProgram.h"

#include <memory>

#include "Shader.h"

namespace black {

ShaderProgram::ShaderProgram(std::shared_ptr<Shader> vertexShader, std::shared_ptr<Shader> fragmentShader)
    : vertexShader(std::move(vertexShader)), fragmentShader(std::move(fragmentShader)) {
}

const std::shared_ptr<Shader> &ShaderProgram::getVertexShader() const {
  return vertexShader;
}

const std::shared_ptr<Shader> &ShaderProgram::getFragmentShader() const {
  return fragmentShader;
}

void ShaderProgram::setVertexShader(const std::shared_ptr<Shader> &newVertexShader) {
  if (newVertexShader->getType() != Shader::Type::VERTEX) {
    throw ShaderProgramInvalidShaderTypeException("Trying to attach invalid shader as vertex shader");
  }
  ShaderProgram::vertexShader = newVertexShader;
}

void ShaderProgram::setFragmentShader(const std::shared_ptr<Shader> &newFragmentShader) {
  if (newFragmentShader->getType() != Shader::Type::FRAGMENT) {
    throw ShaderProgramInvalidShaderTypeException("Trying to attach invalid shader as fragment shader");
  }
  ShaderProgram::fragmentShader = newFragmentShader;
}

bool ShaderProgram::isLinked() const {
  return linked;
}

ShaderProgram::ShaderProgram() = default;

ShaderProgramLinkException::ShaderProgramLinkException(const std::string &message)
    : Exception(message) {}

ShaderProgramInvalidShaderTypeException::ShaderProgramInvalidShaderTypeException(const std::string &message)
    : Exception(message) {}

ShaderProgramNotLinkedException::ShaderProgramNotLinkedException()
    : Exception("Shader program must be linked before use") {}
}
