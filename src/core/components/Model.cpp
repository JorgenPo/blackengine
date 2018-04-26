//
// Created by popof on 23.04.2018.
//

#include "Model.h"

namespace black::components {

    Model::Model(const std::shared_ptr<render::Mesh> &mesh) : mesh(mesh) {}

    Model::Model() {}

    const std::shared_ptr<render::Mesh> &Model::getMesh() const {
        return mesh;
    }

    void Model::setMesh(const std::shared_ptr<render::Mesh> &mesh) {
        Model::mesh = mesh;
    }

    std::shared_ptr<Model> Model::fromFile(std::string fileName) {
        return std::shared_ptr<Model>();
    }
}