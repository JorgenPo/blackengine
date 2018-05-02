//
// Created by popof on 01.05.2018.
//

#include "ExampleApplication.h"
#include <random>
#include <ctime>
#include <core/render/Sprite.h>

void SimpleApplication::initialize() {
    Application::initialize();
    this->core->getCurrentRenderer()->setClearColor(Color(Color::WHITE));

    auto &rm = this->core->getResourceManager();

    // Add resource directory to resource manager
    rm->addResourceFolder("resources/");
    rm->addResourceFolder("resources/morocc");
    rm->addResourceFolder("resources/eclage");
    rm->addResourceFolder("resources/winter_house/");
    rm->addResourceFolder("resources/trees/");
    rm->addResourceFolder("resources/house/");

    auto islandModel = rm->load<Model>("island.fbx");
    auto houseModel = rm->load<Model>("house1.fbx");
    auto statueModel = rm->load<Model>("statue.fbx");

    this->object = std::make_shared<GameEntity>();
    this->object1 = std::make_shared<GameEntity>();
    this->object2 = std::make_shared<GameEntity>();

    this->object->addComponent(islandModel);
    this->object1->addComponent(houseModel);
    this->object2->addComponent(statueModel);

    this->object->transform->setPosition({-200.0f, -75.0f, 50.0f});
    this->object1->transform->setPosition({60.0f, 0.0f, 50.0f});
    this->object2->transform->setPosition({-20.0f, 0.0f, 50.0f});

    auto terrainShader = rm->load<ShaderProgram>("terrain.shader");
    auto terrainTexture = rm->load<Texture>("prontera_grass.bmp");

    auto terrain = std::make_shared<Terrain>(terrainTexture, terrainShader, terrainSize, terrainSize, 5);

    this->mainScene->addEntity(object);
    this->mainScene->addEntity(object1);
    this->mainScene->addEntity(object2);
    this->mainScene->addEntity(terrain);

    this->currentObject = this->object;

    this->generateTrees(150);
    this->generateGrass(1000);
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
    auto &rm = this->core->getResourceManager();

    std::vector<std::shared_ptr<Model>> treeModels;
    try {
        treeModels.push_back(rm->load<Model>("tree1.fbx"));
        treeModels.push_back(rm->load<Model>("tree2.fbx"));
    } catch (const Exception &e) {
        return;
    }

    float area = terrainSize / 2;

    auto modelDistribution = std::uniform_int_distribution<unsigned>(0, treeModels.size() - 1);
    auto positionDistribution = std::uniform_real_distribution<float>(-area, area);

    auto model = std::shared_ptr<Model>();
    float x, z = 0;
    for (int i = 0; i < number; ++i) {
        model = treeModels.at(modelDistribution(generator));

        auto tree = std::make_shared<GameEntity>();
        tree->addComponent(model);

        x = positionDistribution(generator);
        z = positionDistribution(generator);

        tree->transform->setPosition({x, 0.0f, z});

        this->mainScene->addEntity(tree);
    }
}

SimpleApplication::SimpleApplication()
    : Application("SimpleApplication example. BlackEngine v3", 1024, 748), terrainSize(1000.0f)
{
}

void SimpleApplication::generateGrass(int number) {
    auto &rm = this->core->getResourceManager();

    auto grassShader = rm->load<ShaderProgram>("simple.shader");
    auto grassTexture = rm->load<Texture>("leaf_10.bmp");

    float area = terrainSize / 2;

    auto generator = std::mt19937(static_cast<unsigned>(time(nullptr)));
    auto positionDistribution = std::uniform_real_distribution<float>(-area, area);

    float x, z;
    for(int i = 0; i < number; ++i) {
        x = positionDistribution(generator);
        z = positionDistribution(generator);

        auto grassEntity = std::make_shared<Sprite>(grassTexture, grassShader);
        grassEntity->transform->translate({x, 0.0f, z});
        grassEntity->transform->scale(10.0f);

        this->mainScene->addEntity(grassEntity);
    }
}

void SimpleApplication::update() {
    auto pc = this->core->getPerformanceCounter();
    Logger::info("Average mpf = %v; Average fps = %v", pc->getAverageMpf(), pc->getAverageFps());
}
