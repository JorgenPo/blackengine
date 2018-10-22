#include "ShaderProgram.h"

namespace black {

    ShaderProgram::ShaderProgram(const std::shared_ptr<Shader> &vertexShader, const std::shared_ptr<Shader> &fragmentShader)
            : vertexShader(vertexShader), fragmentShader(fragmentShader) {
    }

    const std::shared_ptr<Shader> &ShaderProgram::getVertexShader() const {
        return vertexShader;
    }

    const std::shared_ptr<Shader> &ShaderProgram::getFragmentShader() const {
        return fragmentShader;
    }

    void ShaderProgram::setVertexShader(const std::shared_ptr<Shader> &vertexShader) {
        if (vertexShader->getType() != Shader::Type::VERTEX) {
            throw ShaderProgramInvalidShaderTypeException("Trying to attach invalid shader as vertex shader");
        }
        ShaderProgram::vertexShader = vertexShader;
    }

    void ShaderProgram::setFragmentShader(const std::shared_ptr<Shader> &fragmentShader) {
        if (fragmentShader->getType() != Shader::Type::FRAGMENT) {
            throw ShaderProgramInvalidShaderTypeException("Trying to attach invalid shader as fragment shader");
        }
        ShaderProgram::fragmentShader = fragmentShader;
    }

    bool ShaderProgram::isLinked() const {
        return linked;
    }

    ShaderProgram::ShaderProgram() {

    }

    ShaderProgramLinkException::ShaderProgramLinkException(const std::string &message)
        : Exception(message) {}

    ShaderProgramInvalidShaderTypeException::ShaderProgramInvalidShaderTypeException(const std::string &message)
        : Exception(message) {}

    ShaderProgramNotLinkedException::ShaderProgramNotLinkedException()
        : Exception("Shader program must be linked before use") {}
}
