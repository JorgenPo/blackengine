//
// Created by popof on 30.04.2018.
//

#include <glm/gtc/matrix_transform.hpp>
#include <core/Core.h>
#include "Camera.h"

namespace black {

    Camera::Camera(glm::vec4 viewport, glm::vec3 position, glm::vec3 up, float pitch, float yaw, float roll)
        : up(up), movementSpeed(5.0f), softness(2.0f), zoom(1.0f), viewport(viewport)
    {
        this->worldUp = up;
        this->fov = 45.0f;
        this->fovMin = 1.0f;
        this->fovMax = fov;

        this->nearPlane = 0.1f;
        this->farPlane = 100.0f;
        this->projectionType = ProjectionType::PERSPECTIVE;

        this->aspectRatio = 16.0f / 9.0f;

        this->transform->setPosition(position);
        this->transform->setRotation(glm::vec3{pitch, yaw, roll});
    }

    float Camera::getMovementSpeed() const {
        return movementSpeed;
    }

    void Camera::setMovementSpeed(float movementSpeed) {
        Camera::movementSpeed = movementSpeed;
    }

    float Camera::getSoftness() const {
        return softness;
    }

    void Camera::setSoftness(float softness) {
        Camera::softness = softness;
    }

    float Camera::getZoom() const {
        return zoom;
    }

    void Camera::setZoom(float zoom) {
        Camera::zoom = zoom;
        updateProjectionMatrix();
    }

    glm::mat4 Camera::getProjectionMatrix() {
        return this->projection;
    }

    glm::mat4 Camera::getViewMatrix() {
        return this->view;
    }

    void Camera::setProjectionType(ProjectionType projectionType) {
        Camera::projectionType = projectionType;
    }

    float Camera::getAspectRatio() const {
        return aspectRatio;
    }

    void Camera::setAspectRatio(float aspectRatio) {
        Camera::aspectRatio = aspectRatio;
    }

    float Camera::getFov() const {
        return fov;
    }

    void Camera::setFov(float fov) {
        Camera::fov = fov;
    }

    float Camera::getNearPlane() const {
        return nearPlane;
    }

    void Camera::setNearPlane(float nearPlane) {
        Camera::nearPlane = nearPlane;
    }

    float Camera::getFarPlane() const {
        return farPlane;
    }

    void Camera::setFarPlane(float farPlane) {
        Camera::farPlane = farPlane;
    }

    void Camera::updateProjectionMatrix() {
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

    void Camera::updateViewMatrix() {
        float pitch = this->transform->getRotation().x;
        float yaw = this->transform->getRotation().y;

        glm::vec3 front;
        front.x = static_cast<float>(cos(glm::radians(yaw)) * cos(glm::radians(pitch)));
        front.y = static_cast<float>(sin(glm::radians(pitch)));
        front.z = static_cast<float>(sin(glm::radians(yaw)) * cos(glm::radians(pitch)));

        this->front = glm::normalize(front);
        this->right = glm::normalize(glm::cross(this->front, this->worldUp));
        this->up = glm::normalize(glm::cross(this->right, this->front));

        this->view = glm::lookAt(this->transform->getPosition(), this->transform->getPosition() + this->front, this->up);
    }

    const glm::vec4 &Camera::getViewport() const {
        return viewport;
    }

    void Camera::setViewport(const glm::vec4 &viewport) {
        Camera::viewport = viewport;
    }

    void Camera::updateCamera() {
        this->updateViewMatrix();
        this->updateProjectionMatrix();
    }
}