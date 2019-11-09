//
// Created by popof on 19.04.2018.
//

#include "GameObject.h"

#include <BlackEngine/components/TransformComponent.h>

namespace black {

long long int GameObject::idCounter = 0;

GameObject::GameObject(std::string name) : name(std::move(name)) {
  if (this->name.empty()) {
    this->name = "Entity" + std::to_string(GameObject::idCounter);
  }

  this->add(std::make_shared<TransformComponent>());
  this->transform = this->get<TransformComponent>();
}

const std::string &GameObject::getName() const {
  return name;
}

void GameObject::setName(const std::string &name) {
  GameObject::name = name;
}

GameObject::~GameObject() = default;
}
