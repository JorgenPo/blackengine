//
// Created by popof on 22.04.2018.
//

#include "Shader.h"

namespace black::render {
    Shader::Shader(const std::string &code, Shader::Type type) : source(code), type(type) {

    }

    const std::string &Shader::getSource() const {
        return source;
    }

    void Shader::setSource(const std::string &source) {
        Shader::source = source;
    }

    ShaderCompileException::ShaderCompileException(std::string message) : Exception() {
        this->message = "Shader compiled with errors: " + std::move(message);
    }
}