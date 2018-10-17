//
// Created by popof on 24.09.2018.
//
#include <iostream>
#include <memory>
#include <Engine.h>
#include <application/GameApplication.h>
#include <util/Meshes.h>

using namespace black;

class BlackEngineApplication : public GameApplication {
    std::shared_ptr<Mesh> triangleMesh;

public:
    BlackEngineApplication() : GameApplication(std::string("BlackEngineApplication") + Constants::RuntimePlatformString,
            800, 600, false) {

    }

private:
    void update() override {
        this->renderer->render(this->triangleMesh);
    }

    void initializeResources() override {
        this->triangleMesh = Meshes::create({1.0f, 1.0f, 0.0f});
    }
};

int main(int argc, char **argv) {
    try {
        BlackEngineApplication application;
        application.start();
    } catch(const Exception &e) {
        std::cout << "Failed to start application: " << e.getMessage() << std::endl;
        return 1;
    }

    return 0;
}