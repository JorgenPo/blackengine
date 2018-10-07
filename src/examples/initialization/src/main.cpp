//
// Created by popof on 24.09.2018.
//
#include <iostream>
#include <Engine.h>
#include <application/GameApplication.h>

using namespace black;

class BlackEngineApplication : public GameApplication {
public:
    BlackEngineApplication() : GameApplication(std::string("BlackEngineApplication") + Constants::RuntimePlatformString,
            800, 600, false) {
        //this->logger->info("Starting initialization example");
    }

private:
    void update() override {
    }

    void initializeResources() override {
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