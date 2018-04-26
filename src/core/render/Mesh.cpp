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

    std::shared_ptr<Mesh> Mesh::fromFile(std::string filename) {
        auto core = Core::getInstance();

        std::string extension = FileUtils::getFileExtension(filename);

        auto parser = core->getModelParserForExtension(extension);

        if (parser == nullptr) {
            throw FileFormatUnknownException(extension);
        }

        std::ifstream file(filename);
        if (!file.is_open()) {
            throw FileNotFoundException(filename);
        }

        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        std::vector<float> uvs;

        // Can throw exception
        parser->parse(filename, vertices, indices, uvs);

        auto mesh = core->getCurrentRenderer()->createMesh();
        mesh->setIndices(indices);
        mesh->setVertices(vertices);
        mesh->setTextureCoords(uvs);
        mesh->setPolygonLength(parser->getPolygonLength());

        mesh->update();

        return mesh;
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


}
