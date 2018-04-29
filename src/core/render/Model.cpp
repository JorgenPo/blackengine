//
// Created by popof on 23.04.2018.
//

#include <core/Core.h>
#include "Model.h"

namespace black::render {

    Model::Model(const std::shared_ptr<Mesh> &mesh, const std::shared_ptr<Material> &material)
            : mesh(mesh), material(material) {

    }

    const std::shared_ptr<Mesh> &Model::getMesh() const {
        return mesh;
    }

    void Model::setMesh(const std::shared_ptr<Mesh> &mesh) {
        Model::mesh = mesh;
    }

    const std::shared_ptr<Material> &Model::getMaterial() const {
        return material;
    }

    void Model::setMaterial(const std::shared_ptr<Material> &material) {
        Model::material = material;
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

        auto program = rm->load<ShaderProgram>("simple.shader");
        auto material = std::make_shared<Material>(program);

        return std::make_shared<Model>(mesh, material);
    }

    void Model::render() {
        this->mesh->draw();
    }

    void Model::prepare() {
        this->material->use();
    }
}