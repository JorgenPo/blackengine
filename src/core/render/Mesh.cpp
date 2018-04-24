//
// Created by popof on 22.04.2018.
//

#include <core/Core.h>
#include "Mesh.h"

namespace black::render {
    int Mesh::getVerticesCount() {
        return this->vertices.size();
    }

    std::vector<float> Mesh::getVertices() {
        return this->vertices;
    }

    Mesh::Mesh(std::vector<float> vertices, std::vector<unsigned int> indices)
            : vertices(std::move(vertices)), indices(std::move(indices)) {

    }

    const std::vector<unsigned int> &Mesh::getIndices() const {
        return indices;
    }

    int Mesh::getIndicesCount() {
        return this->indices.size();
    }

    std::shared_ptr<Mesh> Mesh::fromFile(std::string filename) {
        // TODO: implement

        std::vector<float> vertices = {
                0.5f,  0.5f, 0.0f,  // top right
                0.5f, -0.5f, 0.0f,  // bottom right
                -0.5f, -0.5f, 0.0f,  // bottom left
                -0.5f,  0.5f, 0.0f   // top left
        };

        std::vector<unsigned int> indices = {  // note that we start from 0!
                0, 1, 3,   // first triangle
                1, 2, 3    // second triangle
        };

        auto renderer = Core::getInstance()->getCurrentRenderer();

        return renderer->createMesh(vertices, indices);
    }

}
