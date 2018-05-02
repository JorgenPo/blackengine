//
// Created by popof on 02.05.2018.
//

#ifndef BLACKENGINE_SPRITE_H
#define BLACKENGINE_SPRITE_H

#include "core/GameEntity.h"
#include "Model.h"

namespace black::render {
    /**
     * Represents a 2D square mesh with texture
     */
    class Sprite : public GameEntity {
        static std::shared_ptr<Mesh> quadMesh;

    protected:
        std::shared_ptr<Model> model;

    public:
        Sprite(std::shared_ptr<Texture> texture, std::shared_ptr<ShaderProgram> shader);

    private:
        void generateQuadMesh();
    };
}


#endif //BLACKENGINE_SPRITE_H
