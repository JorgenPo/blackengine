//
// Created by popof on 08.05.2018.
//

#ifndef BLACKENGINE_FPSCAMERA_H
#define BLACKENGINE_FPSCAMERA_H

#include <core/Camera.h>

namespace black {

    class FPSCamera : public Camera {
    public:
        FPSCamera *copy() override;

        void handleInput() override;

        void onMouseMoved(ui::Window *window, double xOffset, double yOffset) override;
    };
}


#endif //BLACKENGINE_FPSCAMERA_H
