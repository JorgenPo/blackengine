#include <utility>

//
// Created by popof on 28.10.2018.
//

#include "ModelComponent.h"

#include <render/Mesh.h>
#include <render/Material.h>

#include <algorithm>

namespace black {

std::string ModelComponent::GetName() {
  return "ModelComponent";
}

std::vector<ModelPart> &ModelComponent::getParts() {
  return parts;
}

ModelComponent::ModelComponent(std::vector<ModelPart> parts) : parts(std::move(parts)) {
}

ModelPart &ModelComponent::getPart(const std::string& name) {
  auto foundPart = std::find_if(this->parts.begin(), this->parts.end(), [name](const auto &part) {
    return part.name == name;
  });

  if (foundPart == this->parts.end()) {
    throw ModelPartNotFoundException(name);
  }

  return *foundPart;
}

ModelPart::ModelPart(std::string name, std::shared_ptr<Mesh> mesh, const Material &material)
                     : name(std::move(name)),
                     mesh(std::move(mesh)),
                     material(material) {}

ModelPartNotFoundException::ModelPartNotFoundException(const std::string& partName) : Exception() {
  this->message << "Model part with name '" << partName << "' does not exist" << std::endl;
}
}