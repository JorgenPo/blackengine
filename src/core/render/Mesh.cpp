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

Mesh::Mesh(std::vector<float> vertices, std::vector<float> textureCoords, std::vector<float> normals)
    : vertices(std::move(vertices)), textureCoords(std::move(textureCoords)),
      drawMode(DrawMode::TRIANGLES), polygonSize(3),
      normals(std::move(normals)) {

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

const std::vector<float> &Mesh::getTextureCoords() const {
  return textureCoords;
}

const std::vector<float> &Mesh::getNormals() const {
  return normals;
}

}
