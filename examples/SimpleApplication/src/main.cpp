//
// Created by popof on 16.04.2018.
//
#include <iostream>

#include <core/Application.h>
#include <core/Exception.h>

// Simple example application
class SimpleApplication : public black::Application {
    void initialize() override {
        Application::initialize();
    }
};

int main() {
    SimpleApplication app;

    try {
        return app.run();
    } catch (const black::Exception &e) {
        std::cerr << e.getMessage() << "\n";
        return 1;
    }
}