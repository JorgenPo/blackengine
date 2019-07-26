//
// Created by popof on 15.11.2018.
//

#ifndef BLACKENGINE_CAMERA_H
#define BLACKENGINE_CAMERA_H

#include <common/CommonHeaders.h>
#include <glm/glm.hpp>

namespace black {

enum class ProjectionType {
  PERSPECTIVE,
  ORTHOGRAPHIC
};

/**
 * Represent the camera object holding view and projection matrices
 */
class BLACK_EXPORTED Camera {
protected:
  glm::vec3 position;
  glm::vec3 lookAt;
  glm::vec3 up;

  glm::mat4 viewMatrix{};
  glm::mat4 projectionMatrix{};

  ProjectionType projectionType;

public:
  explicit Camera(ProjectionType projection, const glm::vec3 &position = glm::vec3(0.0f, 0.0f, -1.0f),
         const glm::vec3 &lookAt = glm::vec3(), const glm::vec3 &upVector = glm::vec3(0.0f, 1.0f, 0.0f));

  [[nodiscard]] const glm::mat4 &getViewMatrix() const;
  [[nodiscard]] const glm::mat4 &getProjectionMatrix() const;
  [[nodiscard]] const glm::vec3 &getPosition() const;
  [[nodiscard]] const glm::vec3 &getLookAt() const;
  [[nodiscard]] const glm::vec3 &getUpVector() const;

  void setPosition(const glm::vec3 &newPosition);
  void setLookAt(const glm::vec3 &newLookAt);
  void setUpVector(const glm::vec3 &newUp);

  void strafeRight(float value);
  void strafeLeft(float value);
  void moveForward(float value);
  void moveBackward(float value);

  void setProjection(ProjectionType projection);

private:
  void updateMatrices();
};
}

#endif //BLACKENGINE_CAMERA_H
