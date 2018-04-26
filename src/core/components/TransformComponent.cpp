//
// Created by popof on 23.04.2018.
//

#include "TransformComponent.h"

namespace black::components {
    TransformComponent::TransformComponent()
        : translation(1.0f), rotation(1.0f), scaleMat(1.0f)
    {

    }

    const glm::mat4 &TransformComponent::getTranslation() const {
        return translation;
    }

    const glm::mat4 &TransformComponent::getRotation() const {
        return rotation;
    }

    const glm::mat4 &TransformComponent::getScale() const {
        return scaleMat;
    }

    void TransformComponent::rotate(float angle, glm::vec3 vector) {
        this->rotation = glm::rotate(this->rotation, glm::radians(angle), vector);
    }

    void TransformComponent::rotateX(float angle) {
        this->rotate(angle, {1.0f, 0.0f, 0.0f});
    }

    void TransformComponent::rotateY(float angle) {
        this->rotate(angle, {0.0f, 1.0f, 0.0f});
    }

    void TransformComponent::rotateZ(float angle) {
        this->rotate(angle, {0.0f, 0.0f, 1.0f});
    }

    void TransformComponent::translate(glm::vec3 vector) {
        this->translation = glm::translate(this->translation, vector);
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

    void TransformComponent::scale(glm::vec3 vector) {
        this->scaleMat = glm::scale(this->scaleMat, vector);
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

    const glm::mat4 TransformComponent::getTransformation() const {
        return this->translation * this->rotation * this->scaleMat;
    }

    void TransformComponent::scale(float value) {
        return this->scale(glm::vec3(value));
    }
}