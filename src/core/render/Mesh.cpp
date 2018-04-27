//
// Created by popof on 22.04.2018.
//

#include <core/Core.h>
#include <utility>
#include "Mesh.h"

namespace black::render {
    int Mesh::getVerticesCount() {
        return this->vertices.size();
    }

    std::vector<float> Mesh::getVertices() {
        return this->vertices;
    }

    Mesh::Mesh(std::vector<float> vertices, std::vector<unsigned int> indices, std::vector<float> textureCoords, int polygonLength)
            : vertices(std::move(vertices)), indices(std::move(indices)),
              textureCoords(std::move(textureCoords)), polygonLength(polygonLength) {

    }


    Mesh::Mesh() : polygonLength(3) {

    }


    const std::vector<unsigned int> &Mesh::getIndices() const {
        return indices;
    }

    int Mesh::getIndicesCount() {
        return this->indices.size();
    }

    int Mesh::getPolygonLength() const {
        return polygonLength;
    }

    void Mesh::setPolygonLength(int polygonLength) {
        Mesh::polygonLength = polygonLength;
    }

    void Mesh::setVertices(const std::vector<float> &vertices) {
        Mesh::vertices = vertices;
    }

    void Mesh::setTextureCoords(const std::vector<float> &textureCoords) {
        Mesh::textureCoords = textureCoords;
    }

    void Mesh::setIndices(const std::vector<unsigned int> &indices) {
        Mesh::indices = indices;
    }

    bool Mesh::isInitialized() const {
        return initialized;
    }


}
