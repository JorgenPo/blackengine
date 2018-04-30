//
// Created by popof on 23.04.2018.
//

#include <core/Core.h>
#include <utility>
#include "Model.h"

namespace black::render {

    Model::Model(std::shared_ptr<Mesh> mesh, const MaterialList &materials, const std::vector<std::pair<int, int>> &materialOffsets)
            : mesh(std::move(mesh)), materials(materials), materialOffsets(materialOffsets) {

    }

    const std::shared_ptr<Mesh> &Model::getMesh() const {
        return mesh;
    }

    void Model::setMesh(const std::shared_ptr<Mesh> &mesh) {
        Model::mesh = mesh;
    }

    const MaterialList &Model::getMaterials() const {
        return this->materials;
    }

    void Model::setMaterials(const MaterialList &material) {
        this->materials = material;
    }

    std::shared_ptr<Model> Model::fromFile(std::string filename) {
        auto core = Core::getInstance();
        auto &rm = core->getResourceManager();

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

        Logger::info("Vertices: %v, Polygons: %v", vertices.size() / 3, indices.size() / parser->getPolygonLength());

        auto mesh = core->getCurrentRenderer()->createMesh();
        mesh->setIndices(indices);
        mesh->setVertices(vertices);
        mesh->setTextureCoords(uvs);
        mesh->update();

        return std::make_shared<Model>(mesh, parser->getMaterials(), parser->getMaterialOffsets());
    }

    void Model::render() {
        for (int i = 0; i < this->materialOffsets.size(); i++) {
            this->materials[this->materialOffsets[i].first]->use();

            // Draw only part of mesh
            // materialOffsets[i].first - material index to use
            // materialOffsets[i].second - offset in index buffer of mesh part
            if (i != this->materialOffsets.size() - 1) {
                this->mesh->draw(this->materialOffsets[i].second,
                                 this->materialOffsets[i+1].second - this->materialOffsets[i].second);
            } else {
                this->mesh->draw(this->materialOffsets[i].second,
                                 this->mesh->getIndicesCount() - this->materialOffsets[i].second);
            }
        }
    }
}