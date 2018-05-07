//
// Created by popof on 01.05.2018.
//

#ifndef BLACKENGINE_FPSCAMERA_H
#define BLACKENGINE_FPSCAMERA_H

#include <core/Camera.h>
#include <core/ui/WindowEventListener.h>

namespace black {
    /**
     * First person camera
     */
    class SpectatorCamera : public Camera, public ui::WindowEventListener {
    public:
        SpectatorCamera();

        void updateCamera() override;

        SpectatorCamera *copy() override;

    public:
        void onMouseScrolledDown(ui::Window *window) override;

        void onMouseScrolledUp(ui::Window *window) override;

        void onMouseMoved(ui::Window *window, double xOffset, double yOffset) override;

        void handleInput();
    };
}


#endif //BLACKENGINE_FPSCAMERA_H
