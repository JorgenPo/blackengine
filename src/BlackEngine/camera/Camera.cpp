//
// Created by popof on 15.11.2018.
//

#include "Camera.h"

#include <BlackEngine/log/Logger.h>
#include <BlackEngine/input/InputSystemInterface.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <utility>

namespace black {
Camera::Camera(CameraData data)
    : data(std::move(data)) {
  this->setProjection(getProjectionType());
  this->updateViewMatrix();
}

const glm::mat4 &Camera::getViewMatrix() const {
  return this->viewMatrix;
}

const glm::mat4 &Camera::getProjectionMatrix() const {
  return this->projectionMatrix;
}

const glm::vec3 &Camera::getPosition() const {
  return this->data.position;
}

const glm::vec3 &Camera::getLookAt() const {
  return this->data.lookAt;
}

const glm::vec3 &Camera::getUpVector() const {
  return this->data.up;
}

void Camera::updateViewMatrix() {
  this->viewMatrix = glm::lookAt(
    this->data.position, this->data.position + this->data.lookAt, this->data.up);
}

void Camera::setPosition(const glm::vec3 &newPosition) {
  this->data.position = newPosition;
  this->updateViewMatrix();
}

void Camera::setLookAt(const glm::vec3 &newLookAt) {
  this->data.lookAt = newLookAt;
  this->updateViewMatrix();
}

void Camera::setUpVector(const glm::vec3 &newUp) {
  this->data.up = glm::normalize(newUp);
  this->updateViewMatrix();
}

void Camera::setProjection(ProjectionType projection) {
  this->data.projectionType = projection;
  this->updateProjectionMatrix();
}

void Camera::updateProjectionMatrix() {
  switch (getProjectionType()) {
    case ProjectionType::PERSPECTIVE:
      this->projectionMatrix = glm::perspective(
        45.0f, getRenderTarget()->getRenderTargetAspectRatio(), 0.1f, 100.0f);
      break;
    case ProjectionType::ORTHOGRAPHIC:
      this->projectionMatrix = glm::ortho(
        0.0f, data.renderTarget->getRenderTargetWidth(),
        0.0f, data.renderTarget->getRenderTargetHeight());
      break;
  }
}

const ProjectionType &Camera::getProjectionType() const {
  return data.projectionType;
}

std::shared_ptr<RenderTargetInterface> Camera::getRenderTarget() const {
  return data.renderTarget;
}

void Camera::onEvent(const RenderTargetSizeChanged &event) {
  updateProjectionMatrix();
}

const glm::vec3 &Camera::getRightVector() const {
  return data.right;
}

void Camera::setRightVector(const glm::vec3 &right) {
  data.right = glm::normalize(right);
  updateViewMatrix();
}

glm::vec3 Camera::getDirection() const {
  return data.lookAt - data.position;
}

CameraData::CameraData(
  std::shared_ptr<InputSystemInterface> input,
  std::shared_ptr<RenderTargetInterface> renderTarget,
  std::shared_ptr<AbstractScene> scene,
  ProjectionType projectionType,
  glm::vec3 position)
  : input(std::move(input))
  , renderTarget(std::move(renderTarget))
  , scene(std::move(scene))
  , projectionType(projectionType)
  , position(position) {

}
}