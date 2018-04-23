//
// Created by popof on 23.04.2018.
//

#include "TransformComponent.h"

namespace black::components {
    TransformComponent::TransformComponent()
        : position(), rotation(), scale({1.0f, 1.0f, 1.0f})
    {

    }

    const std::array<float, 3> &TransformComponent::getPosition() const {
        return position;
    }

    void TransformComponent::setPosition(const std::array<float, 3> &position) {
        TransformComponent::position = position;
    }

    const std::array<float, 3> &TransformComponent::getRotation() const {
        return rotation;
    }

    void TransformComponent::setRotation(const std::array<float, 3> &rotation) {
        TransformComponent::rotation = rotation;
    }

    const std::array<float, 3> &TransformComponent::getScale() const {
        return scale;
    }

    void TransformComponent::setScale(const std::array<float, 3> &scale) {
        TransformComponent::scale = scale;
    }
}