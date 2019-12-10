//
// Created by popov on 08.12.2019.
//

#include "RTSCamera.h"

#include <BlackEngine/input/InputSystemInterface.h>
#include <BlackEngine/log/Logger.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace black;

void RTSCamera::strafeRight(float value) {
  strafe(-getRightVector(), value);
}

void RTSCamera::strafeLeft(float value) {
  strafe(getRightVector(), value);
}

void RTSCamera::zoomIn(float value) {
  strafe(getLookAt(), value);
}

void RTSCamera::zoomOut(float value) {
  strafe(-getLookAt(), value);
}

void RTSCamera::handleKeyEvents() {
  if (data.input->isKeyPressed(Key::LEFT)) {
    this->strafeLeft(speed);
  }
  if (data.input->isKeyPressed(Key::RIGHT)) {
    this->strafeRight(speed);
  }
  if (data.input->isKeyPressed(Key::UP)) {
    this->strafeTop(speed);
  }
  if (data.input->isKeyPressed(Key::DOWN)) {
    this->strafeBottom(speed);
  }
}

float RTSCamera::getSpeed() const {
  return speed;
}

void RTSCamera::setSpeed(float newSpeed) {
  speed = newSpeed;
}

void RTSCamera::update() noexcept {
  handleKeyEvents();
  handleMouseEvents();
}

void RTSCamera::strafeTop(float value) {
  strafe(getUpVector(), value);
}

void RTSCamera::strafeBottom(float value) {
  strafe(-getUpVector(), value);
}

void RTSCamera::strafe(const glm::vec3 &vector, float value) {
  auto translate = glm::translate(glm::mat4(1.0f), vector * value);
  setPosition(translate * glm::vec4{getPosition(), 1.0f});
}

void RTSCamera::handleMouseEvents() {
  if (auto scrollY = data.input->getScrollY(); scrollY != 0) {
    strafe(getLookAt(), zoomSpeed * scrollY);
  }

  switch (state) {
    case State::NORMAL:
      handleNormalMouseEvents();
      break;
    case State::CAMERA_MOVING:
      handleMovingMouseEvents();
      break;
    case State::CAMERA_ROTATING:
      handleRotatingMouseEvents();
      break;
  }
}

void RTSCamera::onMouseButtonPressed(const MouseButtonEvent &event) {
  anchorPoint = {data.input->getMouseX(), data.input->getMouseY()};

  if (event.button == MouseButton::RIGHT) {
    state = State::CAMERA_ROTATING;
  } else if (event.button == MouseButton::LEFT) {
    state = State::CAMERA_MOVING;
  }
}

void RTSCamera::onMouseButtonReleased(const MouseButtonEvent &event) {
  state = State::NORMAL;
}

void RTSCamera::handleNormalMouseEvents() {
  // X strafe
  if ((data.renderTarget->getRenderTargetWidth() - data.input->getMouseX()) < borderWidth) {
    strafeRight(speed);
  } else if (data.input->getMouseX() < borderWidth) {
    strafeLeft(speed);
  }

  if ((data.renderTarget->getRenderTargetHeight() - data.input->getMouseY()) < borderWidth) {
    strafeBottom(speed);
  } else if (data.input->getMouseY() < borderWidth) {
    strafeTop(speed);
  }
}

void RTSCamera::handleRotatingMouseEvents() {

}

void RTSCamera::handleMovingMouseEvents() {
  glm::vec2 currentPosition = {data.input->getMouseX(), data.input->getMouseY()};
  auto difference = anchorPoint - currentPosition;

  difference = difference * speed / 8.0f;
  setPosition(data.position - glm::vec3{difference.x, 0.0f, difference.y});
  anchorPoint = currentPosition;
}

std::shared_ptr<Camera> RTSCamera::Factory::create(std::shared_ptr<RenderTargetInterface> renderTarget,
                                                   std::shared_ptr<InputSystemInterface> input,
                                                   ProjectionType projectionType,
                                                   const glm::vec3 &position) const {
  CameraData data;
  data.renderTarget = std::move(renderTarget);
  data.input = std::move(input);
  data.position = position;
  data.lookAt = {0.0f, -1.0f, 0.0f};
  data.up = {0.0f, 0.0f, 1.0f};
  data.right = {1.0f, 0.0f, 0.0f};
  data.projectionType = projectionType;

  auto camera = std::make_shared<RTSCamera>(std::move(data));

  camera->data.input->subscribeForMouseEvents(camera);
  return camera;
}
