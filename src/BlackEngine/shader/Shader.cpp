#include "Shader.h"

#include <memory>

namespace black {
Shader::Shader(std::string code, Shader::Type type) : source(std::move(code)), type(type), compiled(false) {

}

const std::string &Shader::getSource() const {
  return source;
}

void Shader::setSource(const std::string &newSource) {
  Shader::source = newSource;
}

bool Shader::isCompiled() {
  return this->compiled;
}

Shader::Type Shader::getType() const {
  return type;
}

ShaderCompileException::ShaderCompileException(std::string_view message)
  : Exception(fmt::format("Shader compiled with errors: \n{}", message)) {
}
}