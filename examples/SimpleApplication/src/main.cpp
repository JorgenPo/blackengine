//
// Created by popof on 16.04.2018.
//
#include <iostream>

#include <core/Application.h>
#include <core/Exception.h>
#include <core/SharedLibrary.h>
#include <core/os/windows/WindowsSharedLibrary.h>
#include <core/Core.h>
#include <core/render/Model.h>
#include <core/components/TransformComponent.h>

using namespace black;
using namespace black::render;

// Simple example application
class SimpleApplication : public Application {
    std::shared_ptr<GameEntity> object;
    std::shared_ptr<GameEntity> object1;
    std::shared_ptr<GameEntity> object2;

    std::shared_ptr<GameEntity> currentObject;
public:
    void initialize() override {
        Application::initialize();
        this->core->getCurrentRenderer()->setClearColor(Color(Color::WHITE));

        auto &rm = this->core->getResourceManager();

        // Add resource directory to resource manager
        rm->addResourceFolder("resources/");
        rm->addResourceFolder("resources/morocc");
        rm->addResourceFolder("resources/eclage");
        rm->addResourceFolder("resources/winter_house/");

        auto islandModel = rm->load<Model>("island.fbx");
        auto winterHouseModel = rm->load<Model>("winter_house.fbx");
        auto statueModel = rm->load<Model>("statue.fbx");

        this->object = std::make_shared<GameEntity>();
        this->object1 = std::make_shared<GameEntity>();
        this->object2 = std::make_shared<GameEntity>();

        this->object->addComponent(islandModel);
        this->object1->addComponent(winterHouseModel);
        this->object2->addComponent(statueModel);

        this->object->transform->scale(0.5f);

        this->mainScene->addEntity(object);
        //this->mainScene->addEntity(object1);
        //this->mainScene->addEntity(object2);

        this->currentObject = this->object;
    }

    void update() override {
    }

    void onMouseScrolledUp(ui::Window *window) override {
        this->currentObject->transform->scale(1 + 0.005f);
    }

    void onMouseScrolledDown(ui::Window *window) override {
        this->currentObject->transform->scale(1 - 0.005f);
    }

    void processInput() override {
        static float speed = 0.1f;
        auto transform = this->currentObject->getComponent<components::TransformComponent>();

        if (this->mainWindow->isKeyPressed(InputKey::KEY_0)) {
            this->core->getCurrentRenderer()->setClearColor(Color(Color::RED));
        } else if (this->mainWindow->isKeyPressed(InputKey::KEY_1)) {
            this->currentObject = this->object;
        } else if (this->mainWindow->isKeyPressed(InputKey::KEY_2)) {
            this->currentObject = this->object1;
        } else if (this->mainWindow->isKeyPressed(InputKey::KEY_3)) {
            this->currentObject = this->object2;
        } else if (this->mainWindow->isKeyPressed(InputKey::KEY_LEFT)) {
            transform->translateX(-speed);
        } else if (this->mainWindow->isKeyPressed(InputKey::KEY_RIGHT)) {
            transform->translateX(speed);
        } else if (this->mainWindow->isKeyPressed(InputKey::KEY_UP)) {
            transform->translateY(0.01f);
        } else if (this->mainWindow->isKeyPressed(InputKey::KEY_DOWN)) {
            transform->translateY(-0.01f);
        } else if (this->mainWindow->isKeyPressed('+')) {
            transform->scale(1 + speed / 40.0f);
        } else if (this->mainWindow->isKeyPressed('-')) {
            transform->scale(1 - speed / 40.0f);
        } else if (this->mainWindow->isKeyPressed('[')) {
            transform->rotateY(speed);
        } else if (this->mainWindow->isKeyPressed(']')) {
            transform->rotateY(-speed);
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