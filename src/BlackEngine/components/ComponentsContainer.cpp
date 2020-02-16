//
// Created by popov on 15.02.2020.
//

#include "ComponentsContainer.h"

using namespace black;

const std::unordered_map<std::string, std::shared_ptr<Component>> &
ComponentsContainer::getComponents() const {
  return components;
}