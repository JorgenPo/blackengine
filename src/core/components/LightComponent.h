//
// Created by popov on 05.07.2019.
//

#ifndef BLACKENGINE_SRC_CORE_COMPONENTS_LIGHTCOMPONENT_H
#define BLACKENGINE_SRC_CORE_COMPONENTS_LIGHTCOMPONENT_H

#include "Component.h"

#include <Color.h>
#include <glm/vec3.hpp>

namespace black {

enum class LightType {
  DIRECTIONAL, // Direction light without brightness dependency to distance from light
  SPOT, // Same as directional light but with limited area and brightness depends on distance from light source
  POINT, // Point light is a multidirectional light such as lamp
};

/**
 * LightComponent - spot, directed and point light
 */
class BLACK_EXPORTED LightComponent : public Component {
protected:
  LightType type;
  float strength; // from 0 to 1.0f
  glm::vec3 direction;
  Color color;

public:
  static constexpr const char *GetName() { return "LightComponent"; };

  LightComponent(LightType type, float strength, const Color &color,
                 const glm::vec3 &direction = glm::vec3{0.0f, 0.0f, 0.0f});

  [[nodiscard]] LightType getType() const;
  [[nodiscard]] float getStrength() const;
  [[nodiscard]] const glm::vec3 &getDirection() const;
  [[nodiscard]] const Color &getColor() const;

  void setType(LightType type);
  void setStrength(float strength);
  void setDirection(const glm::vec3 &direction);
  void setColor(const Color &color);
};
}

#endif //BLACKENGINE_SRC_CORE_COMPONENTS_LIGHTCOMPONENT_H
