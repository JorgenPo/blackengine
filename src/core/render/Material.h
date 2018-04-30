//
// Created by popof on 24.04.2018.
//

#ifndef BLACKENGINE_MATERIAL_H
#define BLACKENGINE_MATERIAL_H

#include "Texture.h"
#include "ShaderProgram.h"

namespace black::render {
    /**
     * Material class holds a visual properties
     * of object
     */
    class Material {
        std::shared_ptr<Texture> diffuseTexture;
        std::shared_ptr<ShaderProgram> shaderProgram;

    public:
        explicit Material(const std::shared_ptr<ShaderProgram> &shaderProgram);

        const std::shared_ptr<Texture> &getDiffuseTexture() const;

        void setDiffuseTexture(const std::shared_ptr<Texture> &diffuseTexture);
        void setDiffuseTexture(std::string textureName);

        const std::shared_ptr<ShaderProgram> &getShaderProgram() const;

        void setShaderProgram(const std::shared_ptr<ShaderProgram> &shaderProgram);

        void use();
    };
}


#endif //BLACKENGINE_MATERIAL_H
