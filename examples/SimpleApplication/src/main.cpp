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

        this->object->transform->scale(0.01f);

        this->mainScene->addEntity(object);
        this->mainScene->addEntity(object1);
        this->mainScene->addEntity(object2);

        this->currentObject = this->object;
    }

    void update() override {
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