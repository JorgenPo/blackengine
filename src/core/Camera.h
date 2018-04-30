//
// Created by popof on 30.04.2018.
//

#ifndef BLACKENGINE_CAMERA_H
#define BLACKENGINE_CAMERA_H

#include <core/components/CameraComponent.h>
#include "GameEntity.h"

namespace black {

    /**
     * Camera entity
     */
    class Camera : public GameEntity {
    public:
        std::shared_ptr<components::CameraComponent> camera;

        explicit Camera(glm::vec4 viewport);
    };
}


#endif //BLACKENGINE_CAMERA_H
