//
// Created by popov on 05.07.2019.
//

#include "LightComponent.h"

namespace black {

LightComponent::LightComponent(
        LightType type,
        float strength,
        const Color &color,
        const glm::vec3 &direction)

  : type(type), strength(strength), color(color), direction(direction)
{

}

LightType LightComponent::getType() const {
    return type;
}

float LightComponent::getStrength() const {
  return strength;
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

void LightComponent::setStrength(float newStrength) {
  strength = newStrength;
}

void LightComponent::setDirection(const glm::vec3 &newDirection) {
  direction = newDirection;
}

void LightComponent::setColor(const Color &newColor) {
  color = newColor;
}


}