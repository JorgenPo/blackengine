//
// Created by popof on 20.04.2018.
//

#include "GLRenderer.h"
#include "GLFWWindow.h"

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
}
