//
// Created by popof on 09.10.2018.
//

#include "Mesh.h"

namespace black {
    const std::vector<float> &Mesh::getVertices() const {
        return vertices;
    }

    int Mesh::getPolygonSize() const {
        return polygonSize;
    }

    Mesh::Mesh(std::vector<float> vertices)
        : vertices(std::move(vertices)), drawMode(DrawMode::TRIANGLES), polygonSize(3) {

    }

    int Mesh::getDrawMode() const {
        return static_cast<int>(this->drawMode);
    }

    void Mesh::setDrawMode(DrawMode drawMode) {
        Mesh::drawMode = drawMode;
    }

    void Mesh::setPolygonSize(int polygonSize) {
        Mesh::polygonSize = polygonSize;
    }

    size_t Mesh::getVerticesCount() {
        return this->vertices.size() / this->polygonSize;
    }
}
