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
        std::shared_ptr<Texture> mainTexture;
        std::shared_ptr<ShaderProgram> shaderProgram;

    public:
        explicit Material(const std::shared_ptr<ShaderProgram> &shaderProgram);

        const std::shared_ptr<Texture> &getMainTexture() const;

        void setMainTexture(const std::shared_ptr<Texture> &mainTexture);

        const std::shared_ptr<ShaderProgram> &getShaderProgram() const;

        void setShaderProgram(const std::shared_ptr<ShaderProgram> &shaderProgram);
    };
}


#endif //BLACKENGINE_MATERIAL_H
