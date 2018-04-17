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
        auto &core = Core::getInstance();
        auto factories = core.getWindowFactories();

        if (!factories.empty()) {
            auto factory = factories.front();
            factory->setWidth(800);
            factory->setHeight(600);
            factory->setTitle("BlackEngine 2k18 Application");

            this->window = factory->create();
        }

        initialize();
    }

    Application::~Application() {

    }


    int Application::run() {
        if (this->window == nullptr) {
            throw Exception("Window has not been set up");
        }

        this->window->show();

        return 0;
    }

    void Application::initialize() {
        // Subclasses must implement this
    }
}