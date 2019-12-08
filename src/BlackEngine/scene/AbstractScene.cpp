//
// Created by popov on 09.07.2019.
//

#include "AbstractScene.h"
#include "BlackEngine/camera/Camera.h"

#include <BlackEngine/GameObject.h>
#include <BlackEngine/components/BoundingComponent.h>

namespace black {

void AbstractScene::setCurrentCamera(std::shared_ptr<Camera> newCamera) {
  currentCamera = std::move(newCamera);
}

std::shared_ptr<Camera> AbstractScene::getCurrentCamera() const {
  return currentCamera;
}

const AmbientLight &AbstractScene::getAmbientLight() const noexcept {
  return ambientLight;
}

void AbstractScene::setAmbientLight(AmbientLight light) {
  ambientLight = light;
}

std::vector<std::shared_ptr<GameObject>>
AbstractScene::getIntersectingObjects(const Ray &ray, size_t count) const {
  std::vector<std::shared_ptr<GameObject>> objects;

  for (auto i = getObjects().rbegin(); i != getObjects().rend(); i++) {
    const auto &object = *i;

    if (auto bounds = object->get<BoundingComponent>(); bounds != nullptr) {
      if (bounds->isIntersectionEnabled() && !bounds->getIntersectionsWith(ray).empty()) {
        objects.push_back(object);

        if (count-- == 0) {
          return objects;
        }
      }
    }
  }

  return objects;
}

std::shared_ptr<GameObject> AbstractScene::getIntersectingObject(const Ray &ray) const {
  if (auto objects = getIntersectingObjects(ray, 1); objects.empty()) {
    return nullptr;
  } else {
    return objects[0];
  }
}

AbstractScene::~AbstractScene() = default;

}