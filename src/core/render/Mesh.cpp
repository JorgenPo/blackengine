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

black::render::Mesh::Mesh(std::vector<float> vertices) : vertices(std::move(vertices)) {

}
