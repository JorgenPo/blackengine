//
// Created by popof on 01.05.2018.
//

#ifndef BLACKENGINE_TERRAIN_H
#define BLACKENGINE_TERRAIN_H

#include <core/render/Model.h>
#include "GameEntity.h"

namespace black {
    /**
     * Terrain class
     */
    class Terrain : public GameEntity {
    protected:
        std::shared_ptr<render::Model> model;

        float width;
        float height;
        float tileWidth;
        float tileHeight;

    public:
        Terrain(std::shared_ptr<render::Texture> terrainTexture, std::shared_ptr<render::ShaderProgram> terrainShader,
                float width = 200.0f, float height = 200.0f, int levelOfDetails = 10);

        std::shared_ptr<render::Mesh> generateMesh();

        float getPointHeight(size_t xIndex, size_t zIndex);
    };
}


#endif //BLACKENGINE_TERRAIN_H
