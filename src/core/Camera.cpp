//
// Created by popof on 30.04.2018.
//

#include "Camera.h"

namespace black {
    Camera::Camera(glm::vec4 viewport) {
        this->camera = std::make_shared<components::CameraComponent>(viewport);
    }
}
