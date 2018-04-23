//
// Created by popof on 23.04.2018.
//

#include "ModelComponent.h"

namespace black::components {

    ModelComponent::ModelComponent(const std::shared_ptr<render::Mesh> &mesh) : mesh(mesh) {}

    ModelComponent::ModelComponent() {}

    const std::shared_ptr<render::Mesh> &ModelComponent::getMesh() const {
        return mesh;
    }

    void ModelComponent::setMesh(const std::shared_ptr<render::Mesh> &mesh) {
        ModelComponent::mesh = mesh;
    }
}