//
// Created by popof on 23.04.2018.
//

#ifndef BLACKENGINE_TRANSFORMCOMPONENT_H
#define BLACKENGINE_TRANSFORMCOMPONENT_H

#include <array>
#include "Component.h"

namespace black::components {
    /**
     * Component holding transformation data
     */
    class TransformComponent : public Component {
    private:
        std::array<float, 3> position;
        std::array<float, 3> rotation;
        std::array<float, 3> scale;

    public:
        TransformComponent();

        const std::array<float, 3> &getPosition() const;

        void setPosition(const std::array<float, 3> &position);

        const std::array<float, 3> &getRotation() const;

        void setRotation(const std::array<float, 3> &rotation);

        const std::array<float, 3> &getScale() const;

        void setScale(const std::array<float, 3> &scale);
    };
}


#endif //BLACKENGINE_TRANSFORMCOMPONENT_H
