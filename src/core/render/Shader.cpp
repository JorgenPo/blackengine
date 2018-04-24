//
// Created by popof on 22.04.2018.
//

#include <core/FileUtils.h>
#include <fstream>
#include <core/Core.h>
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

    bool Shader::isCompiled() {
        return this->compiled;
    }

    Shader::Type Shader::getType() const {
        return type;
    }

    Shader::Type getShaderTypeByFileName(const std::string &filename) {
        static std::map<std::string, Shader::Type> fileExtensionToType {
                {"vert", Shader::Type::VERTEX},
                {"frag", Shader::Type::FRAGMENT},
                {"geom", Shader::Type::GEOMETRY},
        };

        Shader::Type type;
        std::string fileExtension = FileUtils::getFileExtension(filename);

        // If no type try to assume that it is vertex
        if (fileExtensionToType.find(fileExtension) == fileExtensionToType.end()) {
            return Shader::Type::VERTEX;
        }

        return fileExtensionToType[fileExtension];
    }

    std::shared_ptr<Shader> Shader::fromFile(std::string filename) {

        Shader::Type type = getShaderTypeByFileName(filename);

        std::ifstream file(filename);
        if (!file.is_open()) {
            throw FileNotFoundException(filename);
        }

        std::stringstream buffer;
        buffer << file.rdbuf();

        auto renderer = Core::getInstance()->getCurrentRenderer();
        return renderer->createShader(buffer.str(), type);
    }

    ShaderCompileException::ShaderCompileException(std::string message) : Exception() {
        this->message = "Shader compiled with errors: \n" + std::move(message);
    }
}