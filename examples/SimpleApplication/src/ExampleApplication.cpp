//
// Created by popof on 01.05.2018.
//

#include "ExampleApplication.h"
#include "Player.h"
#include <random>
#include <ctime>
#include <core/render/Sprite.h>

void SimpleApplication::initialize() {
    Application::initialize();
    this->core->getCurrentRenderer()->setClearColor(Color(Color::WHITE));

    auto rm = this->core->getResourceManager();

    // Add resource directory to resource manager
    rm->addResourceFolder("resources/");
    rm->addResourceFolder("resources/morocc");
    rm->addResourceFolder("resources/eclage");
    rm->addResourceFolder("resources/winter_house/");
    rm->addResourceFolder("resources/trees/");
    rm->addResourceFolder("resources/house/");

//    try {
//        this->object = this->mainScene->createEntityWithModel("island.fbx");
//        this->object1 = this->mainScene->createEntityWithModel("house1.fbx");
//        this->object2 = this->mainScene->createEntityWithModel("statue.fbx");
//        this->object->attachChild(this->object2);
//    } catch(const Exception &e) {
//
//    }
//
//    this->object->transform->setPosition({-200.0f, -75.0f, 50.0f});
//    this->object1->transform->setPosition({60.0f, 0.0f, 50.0f});
//    this->object2->transform->setPosition({-20.0f, 100.0f, 50.0f});
//
//    this->currentObject = this->object;
//
//    auto terrain = this->mainScene->createTerrain("prontera_grass.bmp", terrainSize, terrainSize, 5);
//
//    this->player = std::make_shared<Player>("Player", this->mainScene);
//    //this->player->setCamera(this->mainCamera);
//
//    this->generateTrees(150);
//    this->generateGrass(1000);

    auto terrain = this->mainScene->createTerrain("prontera_grass.bmp", terrainSize, terrainSize, 5);
    auto treeEntity = this->mainScene->createEntityWithModel("tree1.fbx");
    auto houseEntity = this->mainScene->createEntityWithModel("house1.fbx");

    houseEntity->attachChild(treeEntity);
    houseEntity->transform->setPosition({0.0f, 0.0f, -100.0f});
    treeEntity->transform->setPosition({0.0f, 20.0f, 0.0f});
    treeEntity->transform->setRotation({0.0f, 0.0f, 15.0f});
}

void SimpleApplication::processInput() {
    if (this->mainWindow->isKeyPressed(InputKey::KEY_1)) {
        this->core->getCurrentRenderer()->setWireframeMode(true);
    }

    if (this->mainWindow->isKeyPressed(InputKey::KEY_2)) {
        this->core->getCurrentRenderer()->setWireframeMode(false);
    }
}

void SimpleApplication::generateTrees(int number) {
    auto generator = std::mt19937(static_cast<unsigned>(time(nullptr)));
    auto rm = this->core->getResourceManager();

    std::vector<std::string> treeModels;
    treeModels.emplace_back("tree1.fbx");
    treeModels.emplace_back("tree2.fbx");


    float area = terrainSize / 2;

    auto modelDistribution = std::uniform_int_distribution<unsigned>(0, treeModels.size() - 1);
    auto positionDistribution = std::uniform_real_distribution<float>(-area, area);

    float x, z = 0;
    std::string prefix = "tree";
    for (int i = 0; i < number; ++i) {
        auto tree = this->mainScene->createEntityWithModel(treeModels.at(modelDistribution(generator)));

        x = positionDistribution(generator);
        z = positionDistribution(generator);

        tree->transform->setPosition({x, 0.0f, z});
    }
}

SimpleApplication::SimpleApplication()
    : Application("SimpleApplication example. BlackEngine v3", 1024, 748), terrainSize(1000.0f)
{
}

void SimpleApplication::generateGrass(int number) {
    float area = terrainSize / 2;

    auto generator = std::mt19937(static_cast<unsigned>(time(nullptr)));
    auto positionDistribution = std::uniform_real_distribution<float>(-area, area);

    float x, z;
    for(int i = 0; i < number; ++i) {
        x = positionDistribution(generator);
        z = positionDistribution(generator);

        try {
            auto grassEntity = this->mainScene->createSprite("leaf_10.bmp");

            grassEntity->transform->translate({x, 0.0f, z});
            grassEntity->transform->scale(10.0f);
        } catch(const scene::EntityCreationException &e) {
            continue;
        }
    }
}

void SimpleApplication::update() {
//    this->object2->transform->rotateY(0.01f);
//    this->player->update();
}

SimpleApplication::~SimpleApplication() {
    black::Logger::info("Average fps: %v", Core::getInstance()->getPerformanceCounter()->getAverageFps());
    black::Logger::info("Average mps: %v", Core::getInstance()->getPerformanceCounter()->getAverageMpf());
    black::Logger::info("Min fps: %v", Core::getInstance()->getPerformanceCounter()->getMinFps());
    black::Logger::info("Max fps: %v", Core::getInstance()->getPerformanceCounter()->getMaxFps());
}
