//
// Created by popof on 20.04.2018.
//

#include <glsl/GLSLShader.h>
#include <glsl/GLSLShaderProgram.h>
#include <core/Core.h>
#include <core/components/ModelComponent.h>
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

    void GLRenderer::initResourcesTemp() {
        auto core = Core::getInstance();
        auto &rm = core->getResourceManager();

        try {
            this->program = rm->load<ShaderProgram>("simple.shader");
            this->mainTexture = rm->load<Texture>("container.jpg");
        } catch (const resources::ResourceNotFoundException &e) {
            std::cerr << e.getMessage() << std::endl;
            std::cerr << "Search paths: " << e.getSearchPaths() << std::endl;
            throw Exception(e.getMessage());
        } catch(const Exception &e) {
            std::cerr << e.getMessage() << std::endl;
        }
    }

    void GLRenderer::render(const GameEntityList &objectList) {
        //Logger::info("Rendering. GL_ERROR = %v", glGetError());

        static bool initialized = false;

        if (!initialized) {
            this->initResourcesTemp();
        }

        initialized = true;

        auto color = this->clearColor;
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        this->program->use();

        // Update uniform
        double timeValue = glfwGetTime();
        this->program->setUniformVariable("time", static_cast<float>(timeValue));

        glActiveTexture(GL_TEXTURE0);
        this->program->setUniformVariable("mainTexture", 0);

        for (const auto &object : objectList) {
            auto model = object->getComponent<components::ModelComponent>();
            auto transform = object->getComponent<components::TransformComponent>();

            if (model == nullptr) {
                continue;
            }

            auto mesh = model->getMesh();

            // Main texture
            this->mainTexture->bind();

            // Set transform matrix
            this->program->setUniformVariable("transform", transform->getTransformation());

            mesh->bind();
            glDrawElements(GL_TRIANGLES, mesh->getIndicesCount(), GL_UNSIGNED_INT, nullptr);
            mesh->unbind();
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
