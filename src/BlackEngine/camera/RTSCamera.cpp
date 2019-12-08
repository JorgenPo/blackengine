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
  updateViewMatrix();

}

void RTSCamera::handleMouseEvents() {
  if (auto scrollY = data.input->getScrollY(); scrollY != 0) {
    strafe(getLookAt(), zoomSpeed * scrollY);
  }
}

std::shared_ptr<Camera> RTSCamera::Factory::create(const CameraData &data) const {
  auto camera = std::make_shared<RTSCamera>(data);

  return camera;
}
