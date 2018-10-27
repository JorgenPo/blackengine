//
// Created by popof on 22.04.2018.
//

#include "GLSLShaderProgram.h"

namespace black {

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

        auto vertexShader = reinterpret_cast<GLuint*>(this->getVertexShader()->getImplementation());
        auto fragmentShader = reinterpret_cast<GLuint*>(this->getFragmentShader()->getImplementation());

        // Attach vertex
        glAttachShader(this->program, *vertexShader);

        // Attach fragment
        glAttachShader(this->program, *fragmentShader);

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
            throw ShaderProgramNotLinkedException();
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
        //glUniform1d(glGetUniformLocation(this->program, name.c_str()), value);
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


    void GLSLShaderProgram::setUniformVariable(const std::string &name, glm::mat4 matrix) {
        glUniformMatrix4fv(glGetUniformLocation(this->program, name.c_str()),
                           1, GL_FALSE, glm::value_ptr(matrix));
    }

    void GLSLShaderProgram::setUniformVariable(const std::string &name, glm::vec3 vector) {
        glUniform3f(glGetUniformLocation(this->program, name.c_str()), vector.r, vector.g, vector.b);
    }
}