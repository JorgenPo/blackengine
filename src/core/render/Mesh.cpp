//
// Created by popof on 22.04.2018.
//

#include "Mesh.h"

int black::render::Mesh::getVerticesCount() {
    return this->vertices.size();
}

std::vector<float> black::render::Mesh::getVertices() {
    return this->vertices;
}

black::render::Mesh::Mesh(std::vector<float> vertices, std::vector<unsigned int> indices)
        : vertices(std::move(vertices)), indices(std::move(indices)) {

}

const std::vector<unsigned int> &black::render::Mesh::getIndices() const {
    return indices;
}

int black::render::Mesh::getIndicesCount() {
    return this->indices.size();
}
