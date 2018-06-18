//
// Created by popof on 01.05.2018.
//

#ifndef BLACKENGINE_SPECTATORCAMERA_H
#define BLACKENGINE_SPECTATORCAMERA_H

#include <core/Camera.h>
#include <core/ui/WindowEventListener.h>

namespace black {
    /**
     * First person camera
     */
    class SpectatorCamera : public Camera {
    public:
        SpectatorCamera *copy() override;

        void onMouseScrolledDown(ui::Window *window) override;

        void onMouseScrolledUp(ui::Window *window) override;

        void onMouseMoved(ui::Window *window, double xOffset, double yOffset) override;

        void handleInput() override;


    };
}


#endif //BLACKENGINE_SPECTATORCAMERA_H
