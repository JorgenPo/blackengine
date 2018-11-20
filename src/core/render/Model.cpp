#include <utility>

//
// Created by popof on 28.10.2018.
//

#include "Model.h"

namespace black {

    std::vector<ModelPart> &Model::getParts() {
        return parts;
    }

    Model::Model(std::vector<ModelPart> parts) : parts(std::move(parts)) {

    }

    ModelPart &Model::getPart(std::string name) {
        auto foundPart = std::find_if(this->parts.begin(), this->parts.end(), [name](const auto &part) {
            return part.name == name;
        });

        if (foundPart == this->parts.end()) {
            throw ModelPartNotFoundException(name);
        }

        return *foundPart;
    }

    ModelPart::ModelPart(const std::string &name, const std::shared_ptr<Mesh> &mesh,
                         const std::shared_ptr<Material> &material) : name(name), mesh(mesh), material(material) {}

    ModelPartNotFoundException::ModelPartNotFoundException(std::string partName) : Exception() {
        this->message << "Model part with name '" << partName << "' does not exist" << std::endl;
    }
}