//
// Created by popof on 15.11.2018.
//

#ifndef BLACKENGINE_CAMERA_H
#define BLACKENGINE_CAMERA_H

#include <CommonHeaders.h>

namespace black {

    enum class ProjectionType {
        PERSPECTIVE,
        ORTHOGRAPHIC
    };

    /**
     * Represent the camera object holding view and projection matrices
     */
    class BLACK_EXPORTED Camera {
    protected:
        glm::vec3 position;
        glm::vec3 lookAt;
        glm::vec3 up;

        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;

        ProjectionType projectionType;

    public:
        Camera(ProjectionType projection, const glm::vec3 &position = glm::vec3(0.0f, 0.0f, -1.0f),
                const glm::vec3 &lookAt = glm::vec3(), const glm::vec3 &upVector = glm::vec3(0.0f, 1.0f, 0.0f));

        const glm::mat4& getViewMatrix() const;
        const glm::mat4& getProjectionMatrix() const;
        const glm::vec3& getPosition() const;
        const glm::vec3& getLookAt() const;
        const glm::vec3& getUpVector() const;

        void setPosition(const glm::vec3 &position);
        void setLookAt(const glm::vec3 &lookAt);
        void setUpVector(const glm::vec3 &up);

        void setProjection(ProjectionType projection);

    private:
        void updateMatrices();
    };
}


#endif //BLACKENGINE_CAMERA_H
