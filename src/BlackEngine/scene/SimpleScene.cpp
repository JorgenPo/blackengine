//
// Created by popov on 09.07.2019.
//

#include "SimpleScene.h"

#include "../GameObject.h"
#include <BlackEngine/Light.h>
#include <BlackEngine/components/LightComponent.h>

#include <algorithm>

namespace black {

void SimpleScene::addObject(std::shared_ptr<GameObject> object) {
  if (object && !hasObject(object->getName())) {
    if (auto lightComponent = object->get<LightComponent>(); lightComponent != nullptr) {
      this->light = std::make_shared<Light>(object);
    }

    objects.emplace_back(std::move(object));
  }
}

void SimpleScene::addObjects(const std::vector<std::shared_ptr<GameObject>> &newObjects) {
  for (auto && object : newObjects) {
    addObject(object);
  }
}

void SimpleScene::removeObject(std::string_view name) {
  auto itemToDelete = getObjectIterator(name);

  if (itemToDelete != objects.end()) {
    if (*itemToDelete == light->getObject()) {
      light.reset();
    }

    objects.erase(itemToDelete);
  }
}

std::shared_ptr<GameObject> SimpleScene::getObject(std::string_view name) const {
  if (auto && object = getObjectIterator(name); object != objects.end()) {
    return *object;
  } else {
    return nullptr;
  }
}

const std::vector<std::shared_ptr<GameObject>> &SimpleScene::getObjects() const {
  return objects;
}

bool SimpleScene::hasObject(std::string_view name) const {
  return getObjectIterator(name) != objects.end();
}

std::vector<std::shared_ptr<GameObject>>::const_iterator SimpleScene::getObjectIterator(std::string_view name) const {
  return std::find_if(objects.cbegin(), objects.cend(),
    [=](auto && object) { return object->getName() == name; });
}

std::string_view SimpleScene::getName() const {
  return sceneName;
}

SimpleScene::SimpleScene(std::string_view name) : sceneName(name) {}

bool SimpleScene::hasLight() const {
  return light != nullptr;
}

std::shared_ptr<Light> SimpleScene::getLight() const {
  return light;
}

}