//
// Created by popof on 02.10.2018.
//

#include "AbstractApplication.h"
#include <Engine.h>

namespace black {

    AbstractApplication::AbstractApplication(const std::string &name, int windowWidth, int windowHeight, bool isFullScreen)
        : name(name), windowWidth(windowWidth), windowHeight(windowHeight), isWindowFullScreen(isFullScreen) {
        this->logger = Logger::Get(name);
    }

    const std::string &AbstractApplication::getName() const {
        return name;
    }

    void AbstractApplication::start() {
        try {
            this->init();
        } catch (const ApplicationInitializationException &e) {
            this->logger->critical("Failed to init an application: {0}", e.getMessage());
            throw;
        }

        this->run();
    }

    AbstractApplication::~AbstractApplication() {
        this->logger->info("Shutdown application");

        Engine::Shutdown();
    }

    void AbstractApplication::setName(const std::string &name) {
        AbstractApplication::name = name;
    }

    int AbstractApplication::getWindowWidth() const {
        return windowWidth;
    }

    void AbstractApplication::setWindowWidth(int windowWidth) {
        AbstractApplication::windowWidth = windowWidth;
    }

    int AbstractApplication::getWindowHeight() const {
        return windowHeight;
    }

    void AbstractApplication::setWindowHeight(int windowHeight) {
        AbstractApplication::windowHeight = windowHeight;
    }

    bool AbstractApplication::isFullScreen() const {
        return isWindowFullScreen;
    }

    void AbstractApplication::setFullScreen(bool isFullScreen) {
        AbstractApplication::isWindowFullScreen = isFullScreen;
    }

    void AbstractApplication::init() {
        this->logger->info("Initializing application");

        Engine::Initialize(this->name, this->windowWidth, this->windowHeight, this->isWindowFullScreen);

        this->logger->info("Initializing application resources");

        // Application resources init
        this->initializeResources();
    }

    ApplicationInitializationException::ApplicationInitializationException(const std::string &message)
        : Exception(message) {}
}