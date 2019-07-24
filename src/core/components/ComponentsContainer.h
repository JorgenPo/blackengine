//
// Created by popof on 23.04.2018.
//

#ifndef BLACKENGINE_COMPONENTSCONTAINER_H
#define BLACKENGINE_COMPONENTSCONTAINER_H

#include "Component.h"

#include <common/CommonHeaders.h>

#include <map>
#include <memory>

namespace black {

/**
 * Container for components
 */
class ComponentsContainer {
  std::map<std::string, std::shared_ptr<Component>> components;

public:
  /**
   * Returns a component with a given name or nullptr
   * if no component found or component type cast
   * failed.
   *
   * @tparam T Type of component to get
   *
   * @param name Name of component
   *
   * @return Requested component
   */
  template<typename T>
  std::shared_ptr<T> get();

  /**
   * Add the component to container
   * @param name A name of component
   * @param component Component
   * @throws ComponentNameAlreadyExist If a given name is busy
   */
  template<typename T>
  void add(const std::shared_ptr<T> &component);
};

template<typename T>
std::shared_ptr<T> ComponentsContainer::get() {
  if (this->components.find(T::GetName()) == this->components.end()) {
    return nullptr;
  }

  return std::dynamic_pointer_cast<T>(this->components.at(T::GetName()));
}

template<typename T>
void ComponentsContainer::add(const std::shared_ptr<T> &component) {
  this->components[T::GetName()] = component;
}

}

#endif //BLACKENGINE_COMPONENTSCONTAINER_H
