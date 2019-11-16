//
// Created by popov on 16.11.2019.
//

#ifndef BLACKENGINE_LIGHT_H
#define BLACKENGINE_LIGHT_H

#include <BlackEngine/GameObject.h>

#include <memory>
#include <glm/vec3.hpp>
#include <BlackEngine/common/Color.h>

namespace black {

class LightComponent;
class TransformComponent;

class DirectionLight {
  std::shared_ptr<GameObject> object;

public:
  explicit DirectionLight(std::shared_ptr<GameObject> object);

  [[nodiscard]] std::shared_ptr<LightComponent> getComponent() const;
  [[nodiscard]] const glm::vec3 &getPosition() const;
  [[nodiscard]] std::shared_ptr<GameObject> getObject() const;
};

struct AmbientLight {
  Color color = Color::WHITE;
  float intensity = 0.1f;
};

}

#endif //BLACKENGINE_LIGHT_H
