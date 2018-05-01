//
// Created by popof on 20.04.2018.
//

#include <glsl/GLSLShader.h>
#include <glsl/GLSLShaderProgram.h>
#include <core/Core.h>
#include <core/render/Model.h>
#include <iostream>
#include <cmath>
#include <core/components/TransformComponent.h>
#include "GLRenderer.h"
#include "GLFWWindow.h"
#include "GLMesh.h"
#include "GLTexture.h"

namespace black::render {

    std::string GLRenderer::getName() {
        return this->rendererName;
    }

    std::shared_ptr<ui::Window> GLRenderer::createRendererWindow(std::string name) {
        // TODO: allow to use different subclasses of GLWindow
        return std::make_shared<ui::GLFWWindow>(std::move(name));
    }

    void GLRenderer::render(const GameEntityList &objectList) {
        static float currentFrame = static_cast<float>(glfwGetTime());
        static float lastFrame = static_cast<float>(glfwGetTime());

        currentFrame = static_cast<float>(glfwGetTime());
        this->deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        double timeValue = glfwGetTime();

        auto color = this->clearColor;
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto viewMatrix = glm::mat4(1.0f);
        auto projectMatrix = glm::mat4(1.0f);

        if (this->rendererView != nullptr) {
            viewMatrix = this->rendererView->getViewMatrix();
            projectMatrix = this->rendererView->getProjectionMatrix();
        }

        for (const auto &object : objectList) {
            auto model = object->getComponent<render::Model>();
            auto transform = object->getComponent<components::TransformComponent>();

            if (model == nullptr) {
                continue;
            }

            // TODO: this is the bad optimization
            // Just assume that all materials using one shader program
            auto program = model->getMaterials().front()->getShaderProgram();

            program->use();

            // Update uniforms
            program->setUniformVariable("time", static_cast<float>(timeValue));
            program->setUniformVariable("transparentColor", {1.0f, 0.0f, 1.0f, 1.0f});

            // Set matrices
            program->setUniformVariable("model", transform->getModelMatrix());
            program->setUniformVariable("projection", projectMatrix);
            program->setUniformVariable("view", viewMatrix);

            // Render all model parts
            model->render();
        }
    }

    std::shared_ptr<Shader> GLRenderer::createShader(const std::string &source, Shader::Type type) {
        return std::make_shared<GLSLShader>(source, type);
    }

    std::shared_ptr<Mesh> GLRenderer::createMesh() {
        return std::make_shared<GLMesh>();
    }

    std::shared_ptr<ShaderProgram> GLRenderer::createShaderProgram() {
        return std::make_shared<GLSLShaderProgram>();
    }

    std::shared_ptr<Texture> GLRenderer::createTexture(std::shared_ptr<Image> image) {
        return std::make_shared<GLTexture>(image);
    }
}
