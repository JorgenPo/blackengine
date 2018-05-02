//
// Created by popof on 01.05.2018.
//

#include "ExampleApplication.h"

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

    this->generateTrees(50);
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
    std::srand(unsigned(std::time(nullptr)));

    auto &rm = this->core->getResourceManager();

    std::vector<std::shared_ptr<Model>> treeModels;
    try {
        treeModels.push_back(rm->load<Model>("tree1.fbx"));
        treeModels.push_back(rm->load<Model>("tree2.fbx"));
    } catch (const Exception &e) {
        return;
    }

    int area = static_cast<int>(terrainSize) / 2;

    auto model = std::shared_ptr<Model>();
    float x, z = 0;
    for (int i = 0; i < number; ++i) {
        model = treeModels.at(rand() % treeModels.size());

        auto tree = std::make_shared<GameEntity>();
        tree->addComponent(model);

        x = rand() % area - area / 2;
        z = rand() % area - area / 2;

        tree->transform->setPosition({x, 0.0f, z});

        this->mainScene->addEntity(tree);
    }
}

SimpleApplication::SimpleApplication()
    : Application("SimpleApplication example. BlackEngine v3", 1024, 748), terrainSize(1000.0f)
{
}
