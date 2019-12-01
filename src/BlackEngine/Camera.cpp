//
// Created by popof on 15.11.2018.
//

#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <utility>
#include <BlackEngine/log/Logger.h>

namespace black {
Camera::Camera(Data data)
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
  this->viewMatrix = glm::lookAt(getPosition(), getLookAt(), getUpVector());
}

void Camera::setPosition(const glm::vec3 &newPosition) {
  this->data.position = newPosition;
  this->updateViewMatrix();
}

void Camera::setLookAt(const glm::vec3 &newLookAt) {
  this->data.lookAt = glm::normalize(newLookAt);
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

void Camera::strafeRight(float value) {
  this->data.position += glm::vec3(value, 0.0f, 0.0f);
  updateViewMatrix();
}

void Camera::strafeLeft(float value) {
  this->data.position -= glm::vec3(value, 0.0f, 0.0f);
  updateViewMatrix();
}

void Camera::moveForward(float value) {
  this->data.position += getLookAt() * value;
  updateViewMatrix();
}

void Camera::moveBackward(float value) {
  this->data.position -= getLookAt() * value;
  updateViewMatrix();
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

Camera::Data::Data(std::shared_ptr<RenderTargetInterface> renderTarget, ProjectionType projection, glm::vec3 position)
  : renderTarget(std::move(renderTarget)), projectionType(projection), position(position) {

}

}