//
// Created by popov on 08.12.2019.
//

#ifndef BLACKENGINE_RTSCAMERA_H
#define BLACKENGINE_RTSCAMERA_H

#include "Camera.h"
#include "CameraFactory.h"

#include <BlackEngine/input/MouseEventSubscriber.h>
#include <BlackEngine/input/KeyboardEventSubscriber.h>

namespace black {

class RTSCamera : public Camera, public MouseEventSubscriber {
  float speed = 0.2f;
  float zoomSpeed = 0.5f;
  float borderWidth = 50.0f;

  enum class State {
    NORMAL,
    CAMERA_ROTATING,
    CAMERA_MOVING,
  };

  State state = State::NORMAL;
  glm::vec2 anchorPoint;        // This point is set to the mouse coords when ROTATING or MOVING state is
                                // triggered
public:
  class Factory : public CameraFactory {
  public:
    static constexpr const char *GetName() {
      return "RTSCamera";
    }

    [[nodiscard]] std::shared_ptr<Camera> create(std::shared_ptr<RenderTargetInterface> renderTarget,
                                                 std::shared_ptr<InputSystemInterface> input,
                                                 ProjectionType projectionType,
                                                 const glm::vec3 &position) const override;
  };

  using Camera::Camera;

  void update() noexcept override;

  float getSpeed() const;

  void setSpeed(float speed);

protected:
  void strafeRight(float value);
  void strafeLeft(float value);
  void strafeTop(float value);
  void strafeBottom(float value);
  void zoomIn(float value);
  void zoomOut(float value);

public:
  void onMouseButtonPressed(const MouseButtonEvent &event) override;

  void onMouseButtonReleased(const MouseButtonEvent &event) override;

private:
  void handleKeyEvents();
  void handleMouseEvents();
  void handleNormalMouseEvents();
  void handleRotatingMouseEvents();
  void handleMovingMouseEvents();
  void strafe(const glm::vec3 &vector, float value);
};

}


#endif //BLACKENGINE_RTSCAMERA_H
