//
// Created by popov on 16.11.2019.
//

#ifndef BLACKENGINE_LIGHT_H
#define BLACKENGINE_LIGHT_H

#include <BlackEngine/GameObject.h>

#include <memory>
#include <glm/vec3.hpp>

namespace black {

class LightComponent;
class TransformComponent;

class Light {
  std::shared_ptr<GameObject> object;

public:
  explicit Light(std::shared_ptr<GameObject> object);

  [[nodiscard]] std::shared_ptr<LightComponent> getComponent() const;
  [[nodiscard]] const glm::vec3 &getPosition() const;

  std::shared_ptr<GameObject> getObject() const;
};

}

#endif //BLACKENGINE_LIGHT_H
