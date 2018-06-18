//
// Created by popof on 08.05.2018.
//

#include <core/Core.h>
#include "FPSCamera.h"

namespace black {
    FPSCamera *FPSCamera::copy() {
        return new FPSCamera();
    }

    void FPSCamera::handleInput() {
        auto window = Core::getInstance()->getEventWindow();

        if (window == nullptr) {
            return;
        }
    }

    void FPSCamera::onMouseMoved(ui::Window *window, double x, double y) {
        static double lastX = x;
        static double lastY = y;

        double xOffset = x - lastX;
        double yOffset = y - lastY;

        lastX = x;
        lastY = y;

        //Take softness into account
        xOffset *= (1.0f - this->softness);
        yOffset *= (1.0f - this->softness);

        this->transform->rotateY(static_cast<float>(xOffset));

        if (this->transform->getRotation().x - yOffset > 90.0f || this->transform->getRotation().x - yOffset < -90.0f)  {
            return;
        }

        this->transform->rotateX(static_cast<float>(-yOffset));
    }
}