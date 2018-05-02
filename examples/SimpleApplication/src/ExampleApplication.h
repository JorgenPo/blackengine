//
// Created by popof on 01.05.2018.
//

#ifndef BLACKENGINE_EXAMPLEAPPLICATION_H
#define BLACKENGINE_EXAMPLEAPPLICATION_H

#include <core/Core.h>
#include <core/Application.h>
#include <core/Terrain.h>

using namespace black;
using namespace black::render;

// Simple example application
class SimpleApplication : public Application {
    std::shared_ptr<GameEntity> object;
    std::shared_ptr<GameEntity> object1;
    std::shared_ptr<GameEntity> object2;

    std::shared_ptr<GameEntity> currentObject;

    float terrainSize;
public:

    SimpleApplication();

    void initialize() override;

    void processInput() override;

    void generateTrees(int number);

    void generateGrass(int number);
};


#endif //BLACKENGINE_EXAMPLEAPPLICATION_H
