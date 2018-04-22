//
// Created by popof on 20.04.2018.
//

#include <glsl/GLSLShader.h>
#include <glsl/GLSLShaderProgram.h>
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

    void GLRenderer::render(const ObjectList &objectList) {
        auto color = this->clearColor;
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT);
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
