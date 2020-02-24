//
// Created by popof on 15.11.2018.
//

#ifndef BLACKENGINE_CAMERA_H
#define BLACKENGINE_CAMERA_H

#include "BlackEngine/common/CommonHeaders.h"

#include <BlackEngine/render/RenderTargetInterface.h>
#include <BlackEngine/input/MouseEventSubscriber.h>

#include <glm/glm.hpp>

#include <memory>


namespace black {

class InputSystemInterface;
class AbstractScene;

enum class ProjectionType {
  PERSPECTIVE,
  ORTHOGRAPHIC
};

struct CameraData {
  CameraData(
    std::shared_ptr<InputSystemInterface> input,
    std::shared_ptr<RenderTargetInterface> renderTarget,
    std::shared_ptr<AbstractScene> scene,
    ProjectionType projectionType,
    glm::vec3 position);

  std::shared_ptr<InputSystemInterface> input;
  std::shared_ptr<RenderTargetInterface> renderTarget;
  std::shared_ptr<AbstractScene> scene;
  ProjectionType projectionType;
  glm::vec3 position;
  glm::vec3 right;
  glm::vec3 lookAt;
  glm::vec3 up;
};

/**
 * Represent the camera object holding view and projection matrices
 */
class BLACK_EXPORTED Camera :
  public EventSubscriber<RenderTargetSizeChanged>,
  public MouseEventSubscriber,
  public std::enable_shared_from_this<Camera> {

protected:
  CameraData data;

private:
  glm::mat4 viewMatrix{};
  glm::mat4 projectionMatrix{};

public:

  explicit Camera(CameraData data);

  virtual void update() = 0;

  [[nodiscard]] const glm::mat4 &getViewMatrix() const;
  [[nodiscard]] const glm::mat4 &getProjectionMatrix() const;
  [[nodiscard]] const glm::vec3 &getPosition() const;
  [[nodiscard]] const glm::vec3 &getLookAt() const;
  [[nodiscard]] const glm::vec3 &getUpVector() const;
  [[nodiscard]] const glm::vec3 &getRightVector() const;
  [[nodiscard]] glm::vec3 getDirection() const;

  [[nodiscard]] const ProjectionType &getProjectionType() const;
  [[nodiscard]] std::shared_ptr<RenderTargetInterface> getRenderTarget() const;

  void setPosition(const glm::vec3 &newPosition);
  void setLookAt(const glm::vec3 &newLookAt);
  void setUpVector(const glm::vec3 &newUp);
  void setRightVector(const glm::vec3 &right);

  void setProjection(ProjectionType projection);

  void onMouseButtonPressed(const MouseButtonEvent &event) override {};
  void onMouseButtonReleased(const MouseButtonEvent &event) override {};
protected:
  void updateProjectionMatrix();
  void updateViewMatrix();
  void onEvent(const RenderTargetSizeChanged &event) override;
};
}

#endif //BLACKENGINE_CAMERA_H
