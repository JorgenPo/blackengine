//
// Created by popov on 05.07.2019.
//

#ifndef BLACKENGINE_SRC_CORE_COMPONENTS_LIGHTCOMPONENT_H
#define BLACKENGINE_SRC_CORE_COMPONENTS_LIGHTCOMPONENT_H

#include "Component.h"

#include "../common/Color.h"
#include <glm/vec3.hpp>

namespace black {

enum class LightType {
  DIRECTED, // Direction light without brightness dependency to distance from light
  SPOT, // Same as directional light but with limited area and brightness depends on distance from light source
  POINT, // Point light is a multidirectional light such as lamp
  AMBIENT,
};

class TransformComponent;

/**
 * LightComponent - base class for all components
 */
class BLACK_EXPORTED LightComponent : public Component {
protected:
  float intensity;
  float spectacularIntensity;
  Color color;

public:
  static constexpr const char *GetName() { return "LightComponent"; };

  explicit LightComponent(const Color &color, float intensity, float spectacularIntensity);

  [[nodiscard]] virtual LightType getType() const = 0;
  [[nodiscard]] float getIntensity() const;
  [[nodiscard]] const Color &getColor() const;
  [[nodiscard]] float getSpectacularIntensity() const;

  void setIntensity(float strength);
  void setColor(const Color &color);
  void setSpectacularIntensity(float spectacularIntensity);
};

class BLACK_EXPORTED DirectedLight : public LightComponent {
protected:
  glm::vec3 direction;

public:
  DirectedLight(const Color &color, float intensity, float spectacularIntensity, const glm::vec3 &direction);

  [[nodiscard]] const glm::vec3 &getDirection() const;

  void setDirection(const glm::vec3 &direction);

  [[nodiscard]] LightType getType() const override;
};

class BLACK_EXPORTED PointLight : public LightComponent {
protected:
  std::shared_ptr<TransformComponent> transform;

public:
  PointLight(
    const Color &color, float intensity, float spectacularIntensity, std::shared_ptr<TransformComponent> transform);

  [[nodiscard]] const glm::vec3 &getPosition() const noexcept;

  [[nodiscard]] LightType getType() const override;
};

struct AmbientLight {
  Color color = Color::WHITE;
  float intensity = 0.1f;
};

std::ostream &operator<<(std::ostream &s, LightType type);

}

#endif //BLACKENGINE_SRC_CORE_COMPONENTS_LIGHTCOMPONENT_H
