//
// Created by popof on 23.04.2018.
//

#ifndef BLACKENGINE_TRANSFORMCOMPONENT_H
#define BLACKENGINE_TRANSFORMCOMPONENT_H

#include <CommonHeaders.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Component.h"

namespace black {
/**
 * Component holding transformation data
 */
class BLACK_EXPORTED TransformComponent : public Component {
private:
  glm::vec3 position;
  glm::vec3 rotation;
  glm::vec3 scaling;

  glm::mat4 modelMatrix;

public:
  static std::string GetName() { return "Transform"; }

  TransformComponent();

  const glm::mat4 getModelMatrix() const;
  const glm::vec3 &getPosition() const;
  const glm::vec3 &getScale() const;
  const glm::vec3 &getRotation() const;

  void setPosition(const glm::vec3 &position);
  void setRotation(const glm::vec3 &rotation);
  void setScale(const glm::vec3 &scaling);

  void rotate(glm::vec3 vector);
  void rotateX(float angle);
  void rotateY(float angle);
  void rotateZ(float angle);

  void translate(glm::vec3 translation);
  void translateX(float value);
  void translateY(float value);
  void translateZ(float value);

  void scale(glm::vec3 scale);
  void scale(float value);
  void scaleX(float value);
  void scaleY(float value);
  void scaleZ(float value);
private:
  void updateModelMatrix();
};
}

#endif //BLACKENGINE_TRANSFORMCOMPONENT_H
