//
// Created by popof on 02.10.2018.
//

#include "AbstractApplication.h"
#include <Engine.h>

namespace black {

    AbstractApplication::AbstractApplication(const std::string &name, int windowWidth, int windowHeight, bool isFullScreen)
        : name(name), windowWidth(windowWidth), windowHeight(windowHeight), isFullScreen(isFullScreen) {
        this->logger = Logger::Get(name);

        this->logger->info("Initializing application");

        Engine::Initialize(this->name, this->windowWidth, this->windowHeight, this->isFullScreen);
    }

    const std::string &AbstractApplication::getName() const {
        return name;
    }

    void AbstractApplication::start() {
        this->logger->info("Initializing application resources");

        // Application resources init
        this->initializeResources();

        this->run();
    }

    AbstractApplication::~AbstractApplication() {
        this->logger->info("Shutdown application");

        Engine::Shutdown();
    }

    ApplicationInitializationException::ApplicationInitializationException(const std::string &message)
        : Exception(message) {}
}