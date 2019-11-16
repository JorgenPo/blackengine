#include "Light.h"

#include <BlackEngine/components/LightComponent.h>
#include <BlackEngine/components/TransformComponent.h>
#include <BlackEngine/exceptions/Exception.h>

using namespace black;

DirectionLight::DirectionLight(std::shared_ptr<GameObject> lightObject) : object(std::move(lightObject)) {
  if (!object->get<LightComponent>()) {
    throw Exception(fmt::format("Game object '{}' hasn't light component", object->getName()));
  }
}

std::shared_ptr<LightComponent> DirectionLight::getComponent() const {
  return object->get<LightComponent>();
}

const glm::vec3 &DirectionLight::getPosition() const {
  return object->transform->getPosition();
}

std::shared_ptr<GameObject> DirectionLight::getObject() const {
  return object;
}
