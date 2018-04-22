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

        std::string vertexShaderSource = "#version 330 core\n"
                                   "layout (location = 0) in vec3 aPos;\n"
                                   "\n"
                                   "void main()\n"
                                   "{\n"
                                   "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                   "}";

        std::string fragmentShaderSource = "#version 330 core\n"
                                           "out vec4 FragColor;\n"
                                           "\n"
                                           "void main()\n"
                                           "{\n"
                                           "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                           "} ";

        auto vertexShader = this->core->getCurrentRenderer()->createShader(vertexShaderSource, Shader::Type::VERTEX);
        auto fragmentShader = this->core->getCurrentRenderer()->createShader(fragmentShaderSource, Shader::Type::FRAGMENT);

        auto triangleMesh = this->core->getCurrentRenderer()->createMesh({});

        try {
            vertexShader->compile();
            fragmentShader->compile();
            auto program = this->core->getCurrentRenderer()->createShaderProgram();
            program->setVertexShader(vertexShader);
            program->setFragmentShader(fragmentShader);
            program->link();

            program->use();
            std::cout << "Shader program built successfully" << std::endl;
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