//
// Created by popof on 16.04.2018.
//
#include <iostream>

#include <core/Application.h>
#include <core/Exception.h>
#include <core/SharedLibrary.h>
#include <core/os/windows/WindowsSharedLibrary.h>
#include <core/Core.h>
#include <core/components/ModelComponent.h>

using namespace black;
using namespace black::render;

// Simple example application
class SimpleApplication : public Application {
public:
    void initialize() override {
        Application::initialize();
        this->core->getCurrentRenderer()->setClearColor(Color(Color::WHITE));

        auto triangleMesh = this->core->getCurrentRenderer()->createMesh({-0.5f, -0.5f, 0.0f,
                                                                           0.5f, -0.5f, 0.0f,
                                                                           0.0f,  0.5f, 0.0f});

        auto entity = std::make_shared<GameEntity>();
        entity->addComponent("Model", std::make_shared<components::ModelComponent>(triangleMesh));
        this->mainScene->addEntity(entity);
    }

    void processInput() override {
        if (this->mainWindow->isKeyPressed(InputKey::KEY_0)) {
            this->core->getCurrentRenderer()->setClearColor(Color(Color::RED));
        } else if (this->mainWindow->isKeyPressed(InputKey::KEY_1)) {
            this->core->getCurrentRenderer()->setClearColor(Color(Color::GREEN));
        } else if (this->mainWindow->isKeyPressed(InputKey::KEY_2)) {
            this->core->getCurrentRenderer()->setClearColor(Color(Color::WHITE));
        } else if (this->mainWindow->isKeyPressed(InputKey::KEY_3)) {
            this->core->getCurrentRenderer()->setClearColor(Color(Color::BLACK));
        }
    }
};

int main() {
    auto core = Core::getInstance();

    try {
        core->initialize();
    } catch (const CoreInitializationException &e) {
        std::cerr << "Failed to init blackengine core. Reason: " << e.getMessage() << std::endl;
        return 1;
    }

    SimpleApplication app;

    try {
        app.initialize();
        return app.run();
    } catch (const Exception &e) {
        std::cerr << e.getMessage() << "\n";
    }

    return 1;
}