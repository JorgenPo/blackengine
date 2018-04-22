//
// Created by popof on 22.04.2018.
//

#include <sstream>
#include "ShaderProgram.h"

namespace black::render {

    ShaderProgram::ShaderProgram(const std::shared_ptr<Shader> &vertexShader,
                                 const std::shared_ptr<Shader> &fragmentShader,
                                 const std::shared_ptr<Shader> &geometryShader)
            : vertexShader(vertexShader), fragmentShader(fragmentShader), geometryShader(geometryShader) {

    }

    const std::shared_ptr<Shader> &ShaderProgram::getVertexShader() const {
        return vertexShader;
    }

    const std::shared_ptr<Shader> &ShaderProgram::getFragmentShader() const {
        return fragmentShader;
    }

    const std::shared_ptr<Shader> &ShaderProgram::getGeometryShader() const {
        return geometryShader;
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

    void ShaderProgram::setGeometryShader(const std::shared_ptr<Shader> &geometryShader) {
        if (geometryShader->getType() != Shader::Type::GEOMETRY) {
            throw ShaderProgramInvalidShaderTypeException("Trying to attach invalid shader as geometry shader");
        }
        ShaderProgram::geometryShader = geometryShader;
    }

    bool ShaderProgram::isLinked() const {
        return linked;
    }

    ShaderProgram::ShaderProgram() = default;

    ShaderProgramLinkException::ShaderProgramLinkException(const std::string &message) : Exception(message) {}

    ShaderProgramInvalidShaderTypeException::ShaderProgramInvalidShaderTypeException(const std::string &message)
            : Exception(message) {}

    ShaderProgramNotLinkedException::ShaderProgramNotLinkedException() : Exception("Shader program must be linked before use") {}
}
