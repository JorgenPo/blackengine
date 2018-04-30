//
// Created by popof on 30.04.2018.
//

#include <glm/gtc/matrix_transform.hpp>
#include <core/Core.h>
#include "CameraComponent.h"

namespace black::components {

    CameraComponent::CameraComponent(glm::vec4 viewport, glm::vec3 position, glm::vec3 up, float pitch, float yaw, float roll)
        : position(position), up(up), pitch(pitch), yaw(yaw), roll(roll),
          movementSpeed(5.0f), softness(2.0f), zoom(1.0f), viewport(viewport)
    {
        this->worldUp = up;
        this->fovMin = 1.0f;
        this->fovMax = fov;

        this->projectionType = ProjectionType::PERSPECTIVE;

        this->updateProjectionMatrix();
        this->updateViewMatrix();
    }

    float CameraComponent::getPitch() const {
        return pitch;
    }

    void CameraComponent::setPitch(float pitch) {
        CameraComponent::pitch = pitch;
        updateViewMatrix();
    }

    float CameraComponent::getYaw() const {
        return yaw;
    }

    void CameraComponent::setYaw(float yaw) {
        CameraComponent::yaw = yaw;
        updateViewMatrix();
    }

    float CameraComponent::getRoll() const {
        return roll;
    }

    void CameraComponent::setRoll(float roll) {
        CameraComponent::roll = roll;
        updateViewMatrix();
    }

    float CameraComponent::getMovementSpeed() const {
        return movementSpeed;
    }

    void CameraComponent::setMovementSpeed(float movementSpeed) {
        CameraComponent::movementSpeed = movementSpeed;
    }

    float CameraComponent::getSoftness() const {
        return softness;
    }

    void CameraComponent::setSoftness(float softness) {
        CameraComponent::softness = softness;
    }

    float CameraComponent::getZoom() const {
        return zoom;
    }

    void CameraComponent::setZoom(float zoom) {
        CameraComponent::zoom = zoom;
        updateProjectionMatrix();
    }

    glm::mat4 CameraComponent::getProjectionMatrix() {
        return this->projection;
    }

    glm::mat4 CameraComponent::getViewMatrix() {
        return glm::mat4();
    }

    void CameraComponent::setProjectionType(ProjectionType projectionType) {
        CameraComponent::projectionType = projectionType;
        this->updateProjectionMatrix();
    }

    float CameraComponent::getAspectRatio() const {
        return aspectRatio;
    }

    void CameraComponent::setAspectRatio(float aspectRatio) {
        CameraComponent::aspectRatio = aspectRatio;
        this->updateProjectionMatrix();
    }

    float CameraComponent::getFov() const {
        return fov;
    }

    void CameraComponent::setFov(float fov) {
        CameraComponent::fov = fov;
        this->updateProjectionMatrix();
    }

    float CameraComponent::getNearPlane() const {
        return nearPlane;
    }

    void CameraComponent::setNearPlane(float nearPlane) {
        CameraComponent::nearPlane = nearPlane;
        this->updateProjectionMatrix();
    }

    float CameraComponent::getFarPlane() const {
        return farPlane;
    }

    void CameraComponent::setFarPlane(float farPlane) {
        CameraComponent::farPlane = farPlane;
        this->updateProjectionMatrix();
    }

    void CameraComponent::updateProjectionMatrix() {
        if (projectionType == ProjectionType::PERSPECTIVE) {
            float zoomedFov = this->fov / this->zoom;
            if (zoomedFov < this->fovMin) zoomedFov = this->fovMin;
            if (zoomedFov > this->fovMax) zoomedFov = this->fovMax;

            this->projection = glm::perspective(glm::radians(zoomedFov), this->aspectRatio,
                    this->nearPlane, this->farPlane);
        } else {
            this->projection = glm::ortho(viewport.x, viewport.z, viewport.y, viewport.w, nearPlane, farPlane);
        }
    }

    void CameraComponent::updateViewMatrix() {
        glm::vec3 front;
        front.x = static_cast<float>(cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch)));
        front.y = static_cast<float>(sin(glm::radians(this->pitch)));
        front.z = static_cast<float>(sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch)));

        this->front = glm::normalize(front);
        this->right = glm::normalize(glm::cross(this->front, this->worldUp));
        this->up = glm::normalize(glm::cross(this->right, this->front));

        this->view = glm::lookAt(this->position, this->position + this->front, this->up);
    }

    const glm::vec4 &CameraComponent::getViewport() const {
        return viewport;
    }

    void CameraComponent::setViewport(const glm::vec4 &viewport) {
        CameraComponent::viewport = viewport;
        this->updateProjectionMatrix();
    }
}