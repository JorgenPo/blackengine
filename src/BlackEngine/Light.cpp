#include "Light.h"

#include <BlackEngine/components/LightComponent.h>
#include <BlackEngine/components/TransformComponent.h>
#include <BlackEngine/exceptions/Exception.h>

using namespace black;

Light::Light(std::shared_ptr<GameObject> lightObject) : object(std::move(lightObject)) {
  if (!object->get<LightComponent>()) {
    throw Exception(fmt::format("Game object '{}' hasn't light component", object->getName()));
  }
}

std::shared_ptr<LightComponent> Light::getComponent() const {
  return object->get<LightComponent>();
}

const glm::vec3 &Light::getPosition() const {
  return object->transform->getPosition();
}

std::shared_ptr<GameObject> Light::getObject() const {
  return object;
}
