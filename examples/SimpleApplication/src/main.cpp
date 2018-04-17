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
    void initialize() override {
        Application::initialize();
    }
};

int main() {
    SimpleApplication app;

    // Loading shared library
    std::unique_ptr<black::SharedLibrary> lib =
            std::make_unique<black::os::WindowsSharedLibrary>("BlackEngine");

    auto& core = black::Core::getInstance();

    try {
        auto& pm = core.getPluginManager();
        pm->loadPlugin("CorePlugin");
    } catch(const black::Exception& e) {
        std::cerr << e.getMessage() << "\n";
        return 2;
    }

    try {
        return app.run();
    } catch (const black::Exception &e) {
        std::cerr << e.getMessage() << "\n";
        return 1;
    }
}