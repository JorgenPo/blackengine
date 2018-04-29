//
// Created by popof on 23.04.2018.
//

#ifndef BLACKENGINE_TRANSFORMCOMPONENT_H
#define BLACKENGINE_TRANSFORMCOMPONENT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Component.h"

namespace black::components {
    /**
     * Component holding transformation data
     */
    class TransformComponent : public Component {
    private:
        glm::mat4 translation;
        glm::mat4 rotation;
        glm::mat4 scaleMat;

    public:
        static std::string getName() { return "Transform"; }

        TransformComponent();

        const glm::mat4 getModelMatrix() const;
        const glm::mat4 &getTranslation() const;
        const glm::mat4 &getRotation() const;
        const glm::mat4 &getScale() const;

        void rotate(float angle, glm::vec3 axis);
        void rotateX(float angle);
        void rotateY(float angle);
        void rotateZ(float angle);

        void translate(glm::vec3 vector);
        void translateX(float value);
        void translateY(float value);
        void translateZ(float value);

        void scale(glm::vec3 vector);
        void scale(float value);
        void scaleX(float value);
        void scaleY(float value);
        void scaleZ(float value);
    };
}


#endif //BLACKENGINE_TRANSFORMCOMPONENT_H
