//
// Created by popof on 01.05.2018.
//

#include <core/Core.h>
#include "SpectatorCamera.h"

namespace black {

    SpectatorCamera::SpectatorCamera() {
        auto eventWindow = Core::getInstance()->getEventWindow();
        if (eventWindow != nullptr) {
            eventWindow->listen(this);
        }
    }

    SpectatorCamera *SpectatorCamera::copy() {
        return new SpectatorCamera();
    }

    void SpectatorCamera::updateCamera() {
        handleInput();

        Camera::updateCamera();
    }

    void SpectatorCamera::handleInput() {
        auto eventWindow = Core::getInstance()->getEventWindow();
        if (eventWindow == nullptr) {
            return;
        }

        if (eventWindow->isKeyPressed(InputKey::KEY_W) || eventWindow->isKeyPressed(InputKey::KEY_UP)) {
            this->moveForward();
        }

        if (eventWindow->isKeyPressed(InputKey::KEY_S) || eventWindow->isKeyPressed(InputKey::KEY_DOWN)) {
            this->moveBackward();
        }

        if (eventWindow->isKeyPressed(InputKey::KEY_A) || eventWindow->isKeyPressed(InputKey::KEY_LEFT)) {
            this->moveLeft();
        }

        if (eventWindow->isKeyPressed(InputKey::KEY_D) || eventWindow->isKeyPressed(InputKey::KEY_RIGHT)) {
            this->moveRight();
        }

        if (eventWindow->isKeyPressed(InputKey::KEY_SPACE)) {
            this->moveUp();
        }
    }

    void SpectatorCamera::onMouseScrolledDown(ui::Window *window) {
        this->setZoom(this->zoom * 0.5f * (1.0f - this->softness));
    }

    void SpectatorCamera::onMouseScrolledUp(ui::Window *window) {
        this->setZoom(this->zoom * 1.5f * (1.0f - this->softness));
    }

    void SpectatorCamera::onMouseMoved(ui::Window *window, double x, double y) {
        static double lastX = x;
        static double lastY = y;

        double xOffset = x - lastX;
        double yOffset = y - lastY;

        lastX = x;
        lastY = y;

        //Take softness into account
        xOffset *= 1.0f - this->softness;
        yOffset *= 1.0f - this->softness;

        this->transform->rotateY(static_cast<float>(xOffset));
        this->transform->rotateX(static_cast<float>(-yOffset));
    }

}