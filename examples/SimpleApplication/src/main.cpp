//
// Created by popof on 16.04.2018.
//
#include <iostream>

#include <core/Application.h>
#include <core/Exception.h>
#include <core/SharedLibrary.h>
#include <core/os/windows/WindowsSharedLibrary.h>
#include <core/Core.h>

using namespace black;
using namespace black::render;

// Simple example application
class SimpleApplication : public Application {
public:
    void initialize() override {
        Application::initialize();
        this->core->getCurrentRenderer()->setClearColor(Color(Color::RED));

        std::string shaderSource = "#version 330 core\n"
                                   "layout (location = 0) in vec3 aPos;\n"
                                   "\n"
                                   "void main()\n"
                                   "{\n"
                                   "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                   "}";

        try {
            auto shader = this->core->getCurrentRenderer()->createShader(shaderSource, Shader::Type::VERTEX);
            shader->compile();
        } catch(const Exception &e) {
            std::cerr << "Failed to compile shader: " + e.getMessage() << std::endl;
        }
    }

    void processInput() override {
        if (this->mainWindow->isKeyPressed(InputKey::KEY_0)) {
            this->core->getCurrentRenderer()->setClearColor(Color(Color::RED));
        } else if (this->mainWindow->isKeyPressed(InputKey::KEY_1)) {
            this->core->getCurrentRenderer()->setClearColor(Color(Color::GREEN));
        } else if (this->mainWindow->isKeyPressed(InputKey::KEY_2)) {
            this->core->getCurrentRenderer()->setClearColor(Color(Color::WHITE));
        } else if (this->mainWindow->isKeyPressed(InputKey::KEY_3)) {
            this->core->getCurrentRenderer()->setClearColor(Color(Color::BLACK));
        }
    }
};

int main() {
    auto core = Core::getInstance();

    try {
        core->initialize();
    } catch (const CoreInitializationException &e) {
        std::cerr << "Failed to init blackengine core. Reason: " << e.getMessage() << std::endl;
        return 1;
    }

    SimpleApplication app;

    try {
        app.initialize();
        return app.run();
    } catch (const Exception &e) {
        std::cerr << e.getMessage() << "\n";
    }

    return 1;
}