//
// Created by popof on 24.04.2018.
//

#include <core/Core.h>
#include "Material.h"

namespace black::render {
    Material::Material(const std::shared_ptr<ShaderProgram> &shaderProgram)
            : diffuseTexture(), shaderProgram(shaderProgram) {}

    const std::shared_ptr<Texture> &Material::getDiffuseTexture() const {
        return diffuseTexture;
    }

    void Material::setDiffuseTexture(const std::shared_ptr<Texture> &mainTexture) {
        Material::diffuseTexture = mainTexture;
    }

    const std::shared_ptr<ShaderProgram> &Material::getShaderProgram() const {
        return shaderProgram;
    }

    void Material::setShaderProgram(const std::shared_ptr<ShaderProgram> &shaderProgram) {
        Material::shaderProgram = shaderProgram;
    }

    void Material::use() {
        this->shaderProgram->use();

        if (this->diffuseTexture != nullptr) {
            this->diffuseTexture->bind();
        }
    }

    void Material::setDiffuseTexture(std::string textureName) {
        try {
            auto texture = Core::GetResourceManager()->load<Texture>(textureName);
            this->setDiffuseTexture(texture);
        } catch(const Exception &e) {
            throw FileNotFoundException(textureName);
        }
    }
}