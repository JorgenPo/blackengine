//
// Created by popof on 23.04.2018.
//

#include "TransformComponent.h"

namespace black {
TransformComponent::TransformComponent()
    : position(0.0f, 0.0f, 0.0f), rotation(0.0f, 0.0f, 0.0f), scaling(1.0f, 1.0f, 1.0f) {
  this->updateModelMatrix();
}

const glm::vec3 &TransformComponent::getPosition() const {
  return position;
}

void TransformComponent::setPosition(const glm::vec3 &position) {
  TransformComponent::position = position;
  this->updateModelMatrix();
}

const glm::vec3 &TransformComponent::getRotation() const {
  return rotation;
}

void TransformComponent::setRotation(const glm::vec3 &rotation) {
  TransformComponent::rotation = rotation;
  this->updateModelMatrix();
}

const glm::vec3 &TransformComponent::getScale() const {
  return scaling;
}

void TransformComponent::setScale(const glm::vec3 &scaling) {
  TransformComponent::scaling = scaling;
  this->updateModelMatrix();
}

const glm::mat4 TransformComponent::getModelMatrix() const {
  return this->modelMatrix;
}

void TransformComponent::updateModelMatrix() {
  glm::mat4 translation = glm::mat4(1.0f);
  glm::mat4 rotation = glm::mat4(1.0f);
  glm::mat4 scale = glm::mat4(1.0f);

  translation = glm::translate(translation, this->position);
  scale = glm::scale(scale, this->scaling);
  rotation = glm::rotate(rotation, glm::radians(this->rotation.x), {1.0f, 0.0f, 0.0f});
  rotation = glm::rotate(rotation, glm::radians(this->rotation.y), {0.0f, 1.0f, 0.0f});
  rotation = glm::rotate(rotation, glm::radians(this->rotation.z), {0.0f, 0.0f, 1.0f});

  this->modelMatrix = translation * rotation * scale;
}

void TransformComponent::rotate(glm::vec3 vector) {
  this->rotation += vector;
  this->updateModelMatrix();
}

void TransformComponent::rotateX(float angle) {
  this->rotate({angle, 0.0f, 0.0f});
}

void TransformComponent::rotateY(float angle) {
  this->rotate({0.0f, angle, 0.0f});
}

void TransformComponent::rotateZ(float angle) {
  this->rotate({0.0f, 0.0f, angle});
}

void TransformComponent::translate(glm::vec3 translation) {
  this->position += translation;
  this->updateModelMatrix();
}

void TransformComponent::translateX(float value) {
  this->translate({value, 0.0f, 0.0f});
}

void TransformComponent::translateY(float value) {
  this->translate({0.0f, value, 0.0f});
}

void TransformComponent::translateZ(float value) {
  this->translate({0.0f, 0.0f, value});
}

void TransformComponent::scale(glm::vec3 scale) {
  this->scaling.x *= scale.x;
  this->scaling.y *= scale.y;
  this->scaling.z *= scale.z;

  this->updateModelMatrix();
}

void TransformComponent::scaleX(float value) {
  this->scale({value, 0.0f, 0.0f});
}

void TransformComponent::scaleY(float value) {
  this->scale({0.0f, value, 0.0f});
}

void TransformComponent::scaleZ(float value) {
  this->scale({0.0f, 0.0f, value});
}

void TransformComponent::scale(float value) {
  this->scaling *= value;
  updateModelMatrix();
}
}