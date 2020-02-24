//
// Created by popov on 24.02.2020.
//

#include "ObjectCamera.h"

#include <BlackEngine/GameObject.h>
#include <BlackEngine/components/TransformComponent.h>

using namespace black;


void ObjectCamera::update() {
  if (!object) {
    return;
  }

  auto position = object->transform->getPosition();
  auto objectPosition = position;

  position.y += height;
  position.z += distance;

  data.position = position;
  data.lookAt = glm::normalize(objectPosition - position);
  data.right = glm::normalize(glm::cross(data.lookAt, data.up));

  updateViewMatrix();
}

ObjectCamera::ObjectCamera(const CameraData &data) : Camera(data)
{

}

void ObjectCamera::setObject(std::shared_ptr<GameObject> newObject) {
  object = std::move(newObject);
}

std::shared_ptr<GameObject> ObjectCamera::getObject() const {
  return object;
}

void ObjectCamera::resetObject() {
  object = nullptr;
}

float ObjectCamera::getHeight() const {
  return height;
}

void ObjectCamera::setHeight(float newHeight) {
  height = newHeight;
}

float ObjectCamera::getDistance() const {
  return distance;
}

void ObjectCamera::setDistance(float newDistance) {
  distance = newDistance;
}

std::shared_ptr<Camera> ObjectCamera::Factory::create(const CameraData &data) const {
  auto camera = std::make_shared<ObjectCamera>(data);
  camera->data.up = glm::vec3{0.0f, 1.0f, 0.0f};

  return camera;
}
