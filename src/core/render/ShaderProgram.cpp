//
// Created by popof on 22.04.2018.
//

#include <sstream>
#include <fstream>
#include <core/Core.h>
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


    std::shared_ptr<ShaderProgram> ShaderProgram::fromFile(const std::string &fileName) {
        std::ifstream file(fileName);
        if (!file.is_open()) {
            throw FileNotFoundException(fileName);
        }

        std::string vertexShaderName;
        std::string fragmentShaderName;

        try {
            file >> vertexShaderName;
            file >> fragmentShaderName;
        } catch(...) {
            throw Exception("Wrong file format");
        }

        auto core = Core::getInstance();
        auto &rm = core->getResourceManager();

        auto shaderProgram = core->getCurrentRenderer()->createShaderProgram();
        std::shared_ptr<Shader> vertexShader;
        std::shared_ptr<Shader> fragmentShader;

        try {
            vertexShader = rm->load<Shader>(vertexShaderName);
            fragmentShader = rm->load<Shader>(fragmentShaderName);
        } catch (const resources::ResourceNotFoundException &e) {
            throw Exception("Can't load shader " + e.getResource());
        } catch (const resources::ResourceLoadingException &e) {
            throw Exception("Wrong shader " + e.getResource());
        }

        try {
            if (!vertexShader->isCompiled()) {
                vertexShader->compile();
            }
            if (!fragmentShader->isCompiled()) {
                fragmentShader->compile();
            }

            shaderProgram->setVertexShader(vertexShader);
            shaderProgram->setFragmentShader(fragmentShader);
            shaderProgram->link();
        } catch (const ShaderCompileException &e) {
            throw Exception("Shader compile error: " + e.getMessage());
        } catch (const ShaderProgramLinkException &e) {
            throw Exception("Program link error: " + e.getMessage());
        }

        return shaderProgram;
    }
}
