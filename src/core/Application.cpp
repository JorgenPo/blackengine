/**
*  BlackEngine - all rights are reserved.
*  3D Game Engine
*  Created by Breezesoftware
**/

#include "Application.h"
#include "Core.h"
#include "Exception.h"

namespace black {


    Application::Application() {
        auto core = Core::getInstance();

        initialize();
    }

    Application::~Application() = default;


    int Application::run() {
        if (this->window == nullptr) {
            throw Exception("Window has not been set up");
        }

        return this->window->run();
    }

    void Application::initialize() {
        // Subclasses must implement this
    }
}