//
// Created by popof on 22.04.2018.
//

#include "GLSLShader.h"

namespace black::render {

    size_t GLSLShader::ERROR_BUFFER_LENGTH = 2048;

    GLSLShader::GLSLShader(const std::string &code, Shader::Type type) : Shader(code, type) {
        this->shader = glCreateShader(toGLShaderType(type));
    }

    void GLSLShader::compile() {
        if (this->source.empty()) {
            throw ShaderCompileException("Shader source is empty");
        }

        auto sourceChars = this->source.c_str();
        glShaderSource(this->shader, 1, &sourceChars, nullptr);
        glCompileShader(this->shader);

        if (!isCompiledSuccessfully()) {
            throw ShaderCompileException(this->getCompilationError());
        }

        this->compiled = true;
    }

    GLenum GLSLShader::toGLShaderType(Shader::Type type) {
        switch (type) {
            case Shader::Type::VERTEX:
                return GL_VERTEX_SHADER;
            case Shader::Type::FRAGMENT:
                return GL_FRAGMENT_SHADER;
            case Shader::Type::GEOMETRY:
                return GL_GEOMETRY_SHADER;
        }
    }

    GLSLShader::~GLSLShader() {
        glDeleteShader(this->shader);
    }

    bool GLSLShader::isCompiledSuccessfully() {
        int success;
        glGetShaderiv(this->shader, GL_COMPILE_STATUS, &success);
        return success == GL_TRUE;
    }

    std::string GLSLShader::getCompilationError() {
        char errorBuffer[ERROR_BUFFER_LENGTH];
        glGetShaderInfoLog(this->shader, sizeof(errorBuffer), nullptr, errorBuffer);

        auto string = std::string(errorBuffer);
        return string;
    }

    void *GLSLShader::getImplementation() {
        return &(this->shader);
    }
}
