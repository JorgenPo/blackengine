//
// Created by popof on 01.05.2018.
//

#include "Terrain.h"
#include <memory>
#include "Core.h"

namespace black {
    Terrain::Terrain(std::shared_ptr<render::Texture> terrainTexture, float width, float height, int levelOfDetails)
        : GameEntity(""), width(width), height(height)
    {
        this->tileWidth = width / levelOfDetails;
        this->tileHeight = height / levelOfDetails;

        auto mesh = this->generateMesh();

        auto renderer = Core::getInstance()->getCurrentRenderer();

        auto material = std::make_shared<render::Material>(renderer->getTerrainShader());
        material->setDiffuseTexture(terrainTexture);

        this->model = render::Model::createSingleMaterialModel(mesh, material);
        this->addComponent(model);
    }

    std::shared_ptr<render::Mesh> Terrain::generateMesh() {
        std::vector<float> vertices;
        std::vector<float> uvs;
        std::vector<unsigned int> indices;

        auto rows = static_cast<size_t>(this->width / this->tileWidth);

        vertices.reserve(rows * rows * 4);

        float xCoord;
        float zCoord;
        float halfWidth = this->width / 2;
        float halfHeight = this->height / 2;
        unsigned int currentIndex = 0;

        for (size_t xIndex = 0; xIndex < rows; xIndex++) {
            for (size_t zIndex = 0; zIndex < rows; zIndex++) {
                xCoord = xIndex * this->tileWidth;
                zCoord = zIndex * this->tileHeight;

                // Add cell vertices
                // Bottom left
                // Terrain must be rendered in center, so adjust x and y

                vertices.push_back(xCoord - halfWidth);
                vertices.push_back(this->getPointHeight(xIndex, zIndex));
                vertices.push_back(zCoord - halfHeight);

                // Top left
                vertices.push_back(xCoord - halfWidth);
                vertices.push_back(this->getPointHeight(xIndex, zIndex));
                vertices.push_back(zCoord + this->tileHeight - halfHeight);

                // Top right
                vertices.push_back(xCoord + this->tileWidth - halfWidth);
                vertices.push_back(this->getPointHeight(xIndex, zIndex));
                vertices.push_back(zCoord + this->tileHeight - halfHeight);

                // Bottom right
                vertices.push_back(xCoord + this->tileWidth - halfWidth);
                vertices.push_back(this->getPointHeight(xIndex, zIndex));
                vertices.push_back(zCoord - halfHeight);

                // Indices
                indices.push_back(currentIndex);
                indices.push_back(currentIndex + 1);
                indices.push_back(currentIndex + 2);

                indices.push_back(currentIndex + 2);
                indices.push_back(currentIndex + 3);
                indices.push_back(currentIndex);

                // UVs
                uvs.push_back(0.0f); uvs.push_back(0.0f);
                uvs.push_back(0.0f); uvs.push_back(1.0f);
                uvs.push_back(1.0f); uvs.push_back(1.0f);
                uvs.push_back(1.0f); uvs.push_back(0.0f);

                currentIndex+=4;
            }
        }

        Logger::info("Land generated. Vertices = %v, polygons = %v", vertices.size(), indices.size() / 3);

        auto mesh = Core::getInstance()->getCurrentRenderer()->createMesh();
        mesh->setVertices(vertices);
        mesh->setIndices(indices);
        mesh->setTextureCoords(uvs);
        mesh->update();

        return mesh;
    }

    float Terrain::getPointHeight(size_t xIndex, size_t zIndex) {
        return 0.0f;
    }


}