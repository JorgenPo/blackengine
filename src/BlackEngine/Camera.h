//
// Created by popof on 15.11.2018.
//

#ifndef BLACKENGINE_CAMERA_H
#define BLACKENGINE_CAMERA_H

#include "common/CommonHeaders.h"

#include <BlackEngine/render/RenderTargetInterface.h>

#include <glm/glm.hpp>

#include <memory>

namespace black {

enum class ProjectionType {
  PERSPECTIVE,
  ORTHOGRAPHIC
};

/**
 * Represent the camera object holding view and projection matrices
 */
class BLACK_EXPORTED Camera :
  public EventSubscriber<RenderTargetSizeChanged>,
  public std::enable_shared_from_this<Camera> {

public:
  struct Data {
    Data(std::shared_ptr<RenderTargetInterface> renderTarget, ProjectionType projection, glm::vec3 position);

    std::shared_ptr<RenderTargetInterface> renderTarget;
    ProjectionType projectionType;
    glm::vec3 position;
    glm::vec3 lookAt = position + glm::vec3{0.0f, 0.0f, -1.0f};
    glm::vec3 up = {0.0f, 1.0f, 0.0f};
  };

private:
  Data data;

  glm::mat4 viewMatrix{};
  glm::mat4 projectionMatrix{};

public:

  explicit Camera(Data data);

  [[nodiscard]] const glm::mat4 &getViewMatrix() const;
  [[nodiscard]] const glm::mat4 &getProjectionMatrix() const;
  [[nodiscard]] const glm::vec3 &getPosition() const;
  [[nodiscard]] const glm::vec3 &getLookAt() const;
  [[nodiscard]] const glm::vec3 &getUpVector() const;
  [[nodiscard]] const ProjectionType &getProjectionType() const;
  [[nodiscard]] std::shared_ptr<RenderTargetInterface> getRenderTarget() const;

  void setPosition(const glm::vec3 &newPosition);
  void setLookAt(const glm::vec3 &newLookAt);
  void setUpVector(const glm::vec3 &newUp);

  void strafeRight(float value);
  void strafeLeft(float value);
  void moveForward(float value);
  void moveBackward(float value);

  void setProjection(ProjectionType projection);
  void updateProjectionMatrix();

  void onEvent(const RenderTargetSizeChanged &event) override;

private:
  void updateViewMatrix();
};
}

#endif //BLACKENGINE_CAMERA_H
