//
// Created by popof on 02.05.2018.
//

#include <core/Core.h>
#include "Sprite.h"

namespace black::render {

    std::shared_ptr<Mesh> Sprite::quadMesh;

    Sprite::Sprite(std::shared_ptr<Texture> texture) : GameEntity("")
    {
        if (Sprite::quadMesh == nullptr) {
            this->generateQuadMesh();
        }

        auto renderer = Core::getInstance()->getCurrentRenderer();

        auto material = std::make_shared<Material>(renderer->getSpriteShader());
        material->setDiffuseTexture(texture);

        this->model = Model::createSingleMaterialModel(quadMesh, material);
        this->addComponent(this->model);
    }

    /**
     * Generates a xy plane quad that used for all sprites
     */
    void Sprite::generateQuadMesh() {
        quadMesh = Core::getInstance()->getCurrentRenderer()->createMesh();

        quadMesh->setVertices({-0.5f, 0.0f, 0.0f,
                               -0.5f, 1.0f, 0.0f,
                               0.5f, 1.0f, 0.0f,
                               0.5f, 0.0f, 0.0f});

        quadMesh->setIndices({
                0, 1, 2,
                2, 0, 3
        });

        quadMesh->setTextureCoords({
                0.0f, 0.0f,
                0.0f, 1.0f,
                1.0f, 1.0f,
                1.0f, 0.0f
        });

        quadMesh->setPolygonLength(3);
        quadMesh->update();
    }
}