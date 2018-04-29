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
        //Logger::info("Rendering. GL_ERROR = %v", glGetError());

        static bool initialized = false;

        if (!initialized) {
            float aspectRatio = this->currentRenderTarget->getRenderTargetAspectRatio();
            this->projectionMatrix = glm::perspective(glm::radians(65.0f), aspectRatio, 0.1f, 100.0f);
            this->viewMatrix = glm::lookAt(glm::vec3{0.0f, 40.2f, 25.5f}, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 1.0f, 0.0f});
        }

        auto color = this->clearColor;
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        double timeValue = glfwGetTime();
        for (const auto &object : objectList) {
            auto model = object->getComponent<render::Model>();
            auto transform = object->getComponent<components::TransformComponent>();

            if (model == nullptr) {
                continue;
            }

            // Use program and bind texture
            model->prepare();

            auto program = model->getMaterial()->getShaderProgram();

            // Update uniforms
            program->setUniformVariable("time", static_cast<float>(timeValue));

            // Set matrices
            program->setUniformVariable("model", transform->getModelMatrix());
            program->setUniformVariable("projection", this->projectionMatrix);
            program->setUniformVariable("view", this->viewMatrix);


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
