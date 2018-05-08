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
        auto color = this->clearColor;
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        this->time = glfwGetTime();

        auto viewMatrix = glm::mat4(1.0f);
        auto projectMatrix = glm::mat4(1.0f);

        if (this->rendererView != nullptr) {
            viewMatrix = this->rendererView->getViewMatrix();
            projectMatrix = this->rendererView->getProjectionMatrix();
        }

        for (const auto &object : objectList) {
            this->renderModel(object, object->transform->getModelMatrix(), viewMatrix, projectMatrix);
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

    void GLRenderer::setWireframeMode(bool on) {
        if (on) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        } else {
            glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
        }
    }

    void GLRenderer::enableFaceCulling(Culling culling) {
        glEnable(GL_CULL_FACE);
        if (culling == Culling::FRONT) {
            glCullFace(GL_FRONT);
        } else if (culling == Culling::BACK) {
            glCullFace(GL_BACK);
        } else {
            glCullFace(GL_FRONT_AND_BACK);
        }
    }

    void GLRenderer::disableFaceCulling() {
        glDisable(GL_CULL_FACE);
    }

    void GLRenderer::setFrontFace(FaceOrdering ordering) {
        if (ordering == FaceOrdering::CW) {
            glFrontFace(GL_CW);
        } else {
            glFrontFace(GL_CCW);
        }
    }

    void GLRenderer::renderModel(const std::shared_ptr<GameEntity> &entity,
                                 glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectMatrix)
    {
        auto model = entity->getComponent<render::Model>();

        // TODO: this is the bad optimization
        // Just assume that all materials using one shader program
        auto program = model->getMaterials().front()->getShaderProgram();

        program->use();

        // Update uniforms
        program->setUniformVariable("time", static_cast<float>(this->time));
        program->setUniformVariable("transparentColor", {1.0f, 0.0f, 1.0f, 1.0f});

        // Set matrices
        program->setUniformVariable("model", modelMatrix);
        program->setUniformVariable("projection", projectMatrix);
        program->setUniformVariable("view", viewMatrix);

        // Render all model parts
        model->render();

        // Render all children entities
        for (const auto &child : entity->getChildren()) {
            auto childModelMatrix = child->transform->getModelMatrix();

            if (child->getComponent<render::Model>() != nullptr) {
                this->renderModel(child, modelMatrix * childModelMatrix, viewMatrix, projectMatrix);
            }
        }
    }
}
