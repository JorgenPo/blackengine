//
// Created by popov on 05.07.2019.
//

#include "LightComponent.h"

namespace black {

LightComponent::LightComponent(
        LightType type,
        float intensity,
        const Color &color,
        const glm::vec3 &direction)

  : type(type), intensity(intensity), color(color), direction(direction), spectacularIntensity(1.0f)
{

}

LightType LightComponent::getType() const {
    return type;
}

float LightComponent::getIntensity() const {
  return intensity;
}

const glm::vec3 &LightComponent::getDirection() const {
  return direction;
}

const Color &LightComponent::getColor() const {
  return color;
}

void LightComponent::setType(LightType newType) {
  type = newType;
}

void LightComponent::setIntensity(float newStrength) {
  intensity = newStrength;
}

void LightComponent::setDirection(const glm::vec3 &newDirection) {
  direction = newDirection;
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


}