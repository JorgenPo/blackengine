//
// Created by popof on 16.04.2018.
//
#include <iostream>

#include <core/Application.h>
#include <core/Exception.h>
#include <core/SharedLibrary.h>
#include <core/os/windows/WindowsSharedLibrary.h>
#include <core/Core.h>

// Simple example application
class SimpleApplication : public black::Application {
public:
    void initialize() override {
        Application::initialize();
        this->core->getCurrentRenderer()->setClearColor(black::Color(black::Color::RED));
    }
};

int main() {
    auto core = black::Core::getInstance();

    try {
        core->initialize();
    } catch (const black::CoreInitializationException &e) {
        std::cerr << "Failed to init blackengine core. Reason: " << e.getMessage() << std::endl;
        return 1;
    }

    SimpleApplication app;

    try {
        app.initialize();
        return app.run();
    } catch (const black::Exception &e) {
        std::cerr << e.getMessage() << "\n";
    }

    return 1;
}