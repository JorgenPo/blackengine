//
// Created by popof on 02.10.2018.
//

#include "GameApplication.h"
#include <Engine.h>

namespace black {

    GameApplication::GameApplication(const std::string &name, int windowWidth, int windowHeight, bool isFullScreen)
        : AbstractApplication(name, windowWidth, windowHeight, isFullScreen) {

        this->setName(std::string("BlackEngine ") + Constants::RuntimePlatformString + " application");
    }

    void GameApplication::run() {
        this->logger->info("Starting application game loop");

        while (!this->window->shouldClose()) {
            this->update();
            this->window->updateRenderTarget();
            this->window->pollEvents();
        }

        this->logger->info("Finishing application game loop");
    }

    void GameApplication::init() {
        AbstractApplication::init();

        auto renderSystem = Engine::GetCurrentRenderSystem();

        try {
            this->logger->info("Creating renderer and render window");

            this->renderer = renderSystem->getRenderer();
            this->window = renderSystem->getRenderWindow();
        } catch (const Exception &e) {
            throw ApplicationInitializationException(e.getMessage());
        }
    }
}