//
// Created by popof on 20.04.2018.
//

#include <glsl/GLSLShader.h>
#include <glsl/GLSLShaderProgram.h>
#include <core/Core.h>
#include <core/components/ModelComponent.h>
#include <iostream>
#include "GLRenderer.h"
#include "GLFWWindow.h"
#include "GLMesh.h"

namespace black::render {

    std::string GLRenderer::getName() {
        return this->rendererName;
    }

    std::shared_ptr<ui::Window> GLRenderer::createRendererWindow(std::string name) {
        // TODO: allow to use different subclasses of GLWindow
        return std::make_shared<ui::GLFWWindow>(std::move(name));
    }

    void GLRenderer::initProgram() {

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


        auto core = Core::getInstance();
        this->program = this->createShaderProgram();
        auto vertexShader = this->createShader(vertexShaderSource, Shader::Type::VERTEX);
        auto fragmentShader = this->createShader(fragmentShaderSource, Shader::Type::FRAGMENT);

        try {
            vertexShader->compile();
            fragmentShader->compile();
            this->program->setVertexShader(vertexShader);
            this->program->setFragmentShader(fragmentShader);
            this->program->link();
        } catch(const Exception &e) {
        }
    }

    void GLRenderer::render(const GameEntityList &objectList) {

        static bool initialized = false;

        this->initProgram();

        initialized = true;

        auto color = this->clearColor;
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT);

        this->program->use();
        for (const auto &object : objectList) {
            auto model = object->getComponent<components::ModelComponent>("Model");
            if (model == nullptr) {
                continue;
            }

            model->getMesh()->bind();
            glDrawArrays(GL_TRIANGLES, 0, model->getMesh()->getVerticesCount());
        }
    }

    std::shared_ptr<Shader> GLRenderer::createShader(std::string source, Shader::Type type) {
        return std::make_shared<GLSLShader>(source, type);
    }

    std::shared_ptr<Mesh> GLRenderer::createMesh(std::vector<float> vertices) {
        return std::make_shared<GLMesh>(vertices);
    }

    std::shared_ptr<ShaderProgram> GLRenderer::createShaderProgram() {
        return std::make_shared<GLSLShaderProgram>();
    }
}
