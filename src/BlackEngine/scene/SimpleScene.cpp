//
// Created by popov on 09.07.2019.
//

#include "SimpleScene.h"

#include "../GameObject.h"

#include <algorithm>

namespace black {

void SimpleScene::addObject(std::shared_ptr<GameObject> object) {
  if (!hasObject(object->getName())) {
    objects.emplace_back(std::move(object));
  }
}

void SimpleScene::addObjects(const std::vector<std::shared_ptr<GameObject>> &newObjects) {
  std::copy_if(newObjects.begin(), newObjects.end(), std::back_inserter(objects),
    [=](auto && object) { return !hasObject(object->getName()); });
}

void SimpleScene::removeObject(std::string_view name) {
  objects.erase(getObjectIterator(name));
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
}