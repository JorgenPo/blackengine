//
// Created by popof on 22.04.2018.
//

#include "GLSLShaderProgram.h"

namespace black::render {

    size_t GLSLShaderProgram::ERROR_BUFFER_LENGTH = 2048;

    GLSLShaderProgram::GLSLShaderProgram() {
        this->program = glCreateProgram();
    }

    void GLSLShaderProgram::link() {
        if (this->getVertexShader() == nullptr || this->getFragmentShader() == nullptr) {
            throw ShaderProgramLinkException("Vertex shader and fragment shader are required to link shader program");
        }

        if (!this->getVertexShader()->isCompiled()) {
            throw ShaderProgramLinkException("Vertex shader not compiled");
        }
        if (!this->getFragmentShader()->isCompiled()) {
            throw ShaderProgramLinkException("Fragment shader not compiled");
        }
        if (this->getGeometryShader() != nullptr && !this->getGeometryShader()->isCompiled()) {
            throw ShaderProgramLinkException("Geometry shader not compiled");
        }

        // TODO: FIX POSSIBLE RUNTIME EXCEPTIONS
        auto vertexShader = reinterpret_cast<GLuint*>(this->getVertexShader()->getImplementation());
        auto fragmentShader = reinterpret_cast<GLuint*>(this->getFragmentShader()->getImplementation());

        // Attach vertex
        glAttachShader(this->program, *vertexShader);
        // Attach fragment
        glAttachShader(this->program, *fragmentShader);

        if (this->getGeometryShader() != nullptr) {
            auto geometryShader = reinterpret_cast<GLuint*>(this->getGeometryShader()->getImplementation());
            glAttachShader(this->program, *geometryShader);
        }

        glLinkProgram(this->program);

        if (!this->isLinkedSuccessfully()) {
            throw ShaderProgramLinkException(this->getLinkError());
        }

        this->linked = true;
    }

    bool GLSLShaderProgram::isLinkedSuccessfully() {
        GLint status = GL_FALSE;
        glGetProgramiv(this->program, GL_LINK_STATUS, &status);

        return status == GL_TRUE;
    }

    std::string GLSLShaderProgram::getLinkError() {
        char errorBuffer[ERROR_BUFFER_LENGTH];
        glGetProgramInfoLog(this->program, sizeof(errorBuffer), nullptr, errorBuffer);

        auto string = std::string(errorBuffer);
        return string;
    }

    GLSLShaderProgram::~GLSLShaderProgram() {
        glDeleteProgram(this->program);
    }

    void GLSLShaderProgram::use() {
        if (!this->isLinked()) {
        }
        glUseProgram(this->program);
    }

    void GLSLShaderProgram::setUniformVariable(const std::string &name, int value) {
        glUniform1i(glGetUniformLocation(this->program, name.c_str()), value);
    }

    void GLSLShaderProgram::setUniformVariable(const std::string &name, float value) {
        glUniform1f(glGetUniformLocation(this->program, name.c_str()), value);
    }

    void GLSLShaderProgram::setUniformVariable(const std::string &name, bool value) {
        glUniform1i(glGetUniformLocation(this->program, name.c_str()), value);
    }

    void GLSLShaderProgram::setUniformVariable(const std::string &name, double value) {
        glUniform1d(glGetUniformLocation(this->program, name.c_str()), value);
    }

    void GLSLShaderProgram::setUniformVariable(const std::string &name, std::array<float, 4> value) {
        glUniform4f(glGetUniformLocation(this->program, name.c_str()), value[0], value[1], value[2], value[3]);
    }

    void GLSLShaderProgram::setUniformVariable(const std::string &name, std::array<float, 3> value) {
        glUniform3f(glGetUniformLocation(this->program, name.c_str()), value[0], value[1], value[2]);
    }

    void GLSLShaderProgram::setUniformVariable(const std::string &name, std::array<float, 2> value) {
        glUniform2f(glGetUniformLocation(this->program, name.c_str()), value[0], value[1]);
    }
}