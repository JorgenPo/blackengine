//
// Created by popof on 30.04.2018.
//

#ifndef BLACKENGINE_CAMERACOMPONENT_H
#define BLACKENGINE_CAMERACOMPONENT_H

#include <glm/glm.hpp>
#include "Component.h"

namespace black::components {

    enum class ProjectionType {
        ORTHOGRAPHIC,
        PERSPECTIVE
    };

    /**
     * Camera component class
     */
    class CameraComponent : public Component {
    protected:
        glm::vec3 position;
        glm::vec3 worldUp;
        glm::vec3 up;
        glm::vec3 front;
        glm::vec3 right;

        float pitch;
        float yaw;
        float roll;

        float movementSpeed;
        float softness;
        float zoom;

        glm::mat4 view;
        glm::mat4 projection;
        ProjectionType projectionType;

        float aspectRatio;

        float fov;
        float fovMin;
        float fovMax;

        float nearPlane;
        float farPlane;

        glm::vec4 viewport;
    public:
        explicit CameraComponent(glm::vec4 viewport, glm::vec3 position = {0.0f, 0.0f, 0.0f},
                glm::vec3 up = {0.0f, 1.0f, 0.0f},
                float pitch = 0.0f, float yaw = -90.0f, float roll = 0.0f);

        float getPitch() const;

        void setPitch(float pitch);

        float getYaw() const;

        void setYaw(float yaw);

        float getRoll() const;

        void setRoll(float roll);

        float getMovementSpeed() const;

        void setMovementSpeed(float movementSpeed);

        float getSoftness() const;

        void setSoftness(float softness);

        float getZoom() const;

        void setZoom(float zoom);

        glm::mat4 getProjectionMatrix();
        glm::mat4 getViewMatrix();

        void setProjectionType(ProjectionType projectionType);

        float getAspectRatio() const;

        void setAspectRatio(float aspectRatio);

        float getFov() const;

        void setFov(float fov);

        float getNearPlane() const;

        void setNearPlane(float nearPlane);

        float getFarPlane() const;

        void setFarPlane(float farPlane);

        const glm::vec4 &getViewport() const;

        void setViewport(const glm::vec4 &viewport);

    private:
        void updateProjectionMatrix();
        void updateViewMatrix();
    };
}


#endif //BLACKENGINE_CAMERACOMPONENT_H