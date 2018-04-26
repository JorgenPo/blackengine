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
#include <core/components/TransformComponent.h>

using namespace black;
using namespace black::render;

// Simple example application
class SimpleApplication : public Application, public ui::WindowEventListener {
    std::shared_ptr<GameEntity> cube;

public:
    void initialize() override {
        Application::initialize();
        this->core->getCurrentRenderer()->setClearColor(Color(Color::WHITE));

        // Add resource directory to resource manager
        this->core->getResourceManager()->addResourceFolder("resources/");

        auto triangleMesh = this->core->getResourceManager()->load<Mesh>("model.bmf");

        this->cube = std::make_shared<GameEntity>();
        this->cube->addComponent(std::make_shared<components::ModelComponent>(triangleMesh));
        this->mainScene->addEntity(this->cube);

        this->mainWindow->listen(this);
    }

    void onMouseScrolledUp(ui::Window *window) override {
        static float speed = 0.1;
        this->cube->transform->scale(1.0f + speed);
    }

    void onMouseScrolledDown(ui::Window *window) override {
        static float speed = 0.1;
        this->cube->transform->scale(1.0f - speed);
    }

    void processInput() override {
        static float angle = 0.1f;
        auto transform = this->cube->getComponent<components::TransformComponent>();

        if (this->mainWindow->isKeyPressed(InputKey::KEY_0)) {
            this->core->getCurrentRenderer()->setClearColor(Color(Color::RED));
        } else if (this->mainWindow->isKeyPressed(InputKey::KEY_1)) {
            this->core->getCurrentRenderer()->setClearColor(Color(Color::GREEN));
        } else if (this->mainWindow->isKeyPressed(InputKey::KEY_2)) {
            this->core->getCurrentRenderer()->setClearColor(Color(Color::WHITE));
        } else if (this->mainWindow->isKeyPressed(InputKey::KEY_3)) {
            this->core->getCurrentRenderer()->setClearColor(Color(Color::BLACK));
        } else if (this->mainWindow->isKeyPressed(InputKey::KEY_LEFT)) {
            transform->rotateY(angle);
        } else if (this->mainWindow->isKeyPressed(InputKey::KEY_RIGHT)) {
            transform->rotateY(-angle);
        } else if (this->mainWindow->isKeyPressed(InputKey::KEY_UP)) {
            transform->rotateX(angle);
        } else if (this->mainWindow->isKeyPressed(InputKey::KEY_DOWN)) {
            transform->rotateX(-angle);
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