//
// Created by popov on 05.07.2019.
//

#include "LightComponent.h"
#include "TransformComponent.h"

namespace black {

LightComponent::LightComponent(
        const Color &color,
        float intensity,
        float spectacularIntensity)

  : color(color), intensity(intensity), spectacularIntensity(spectacularIntensity)
{

}

float LightComponent::getIntensity() const {
  return intensity;
}

const Color &LightComponent::getColor() const {
  return color;
}

void LightComponent::setIntensity(float newStrength) {
  intensity = newStrength;
}

void LightComponent::setColor(const Color &newColor) {
  color = newColor;
}

float LightComponent::getSpectacularIntensity() const {
  return spectacularIntensity;
}

void LightComponent::setSpectacularIntensity(float newIntensity) {
  spectacularIntensity = newIntensity;
}

///////////////////////////////////////////////////////////////////////////////////////

DirectedLight::DirectedLight(
  const Color &color,
  float intensity,
  float spectacularIntensity,
  const glm::vec3 &direction)
  : LightComponent(color, intensity, spectacularIntensity)
  , direction(glm::normalize(direction)) {

}

const glm::vec3 &DirectedLight::getDirection() const {
  return direction;
}

void DirectedLight::setDirection(const glm::vec3 &newDirection) {
  direction = glm::normalize(newDirection);
}

LightType DirectedLight::getType() const {
  return LightType::DIRECTED;
}

PointLight::PointLight(
  const Color &color,
  float intensity,
  float spectacularIntensity,
  std::shared_ptr<TransformComponent> transform)
  : LightComponent(color, intensity, spectacularIntensity), transform(std::move(transform)) {

}

const glm::vec3 &PointLight::getPosition() const noexcept {
  return transform->getPosition();
}

LightType PointLight::getType() const {
  return LightType::POINT;
}
}