//
// Created by popof on 24.04.2018.
//

#include "Material.h"

namespace black::render {
    Material::Material(const std::shared_ptr<ShaderProgram> &shaderProgram)
            : mainTexture(), shaderProgram(shaderProgram) {}

    const std::shared_ptr<Texture> &Material::getMainTexture() const {
        return mainTexture;
    }

    void Material::setMainTexture(const std::shared_ptr<Texture> &mainTexture) {
        Material::mainTexture = mainTexture;
    }

    const std::shared_ptr<ShaderProgram> &Material::getShaderProgram() const {
        return shaderProgram;
    }

    void Material::setShaderProgram(const std::shared_ptr<ShaderProgram> &shaderProgram) {
        Material::shaderProgram = shaderProgram;
    }
}