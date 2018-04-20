//
// Created by popof on 20.04.2018.
//

#include "GLRenderer.h"
#include "GLFWWindow.h"

namespace black::render {

    std::string GLRenderer::getName() {
        return this->rendererName;
    }

    std::shared_ptr<ui::Window> GLRenderer::createRendererWindow() {
        // TODO: allow to use different subclasses of GLWindow
        return std::make_shared<ui::GLFWWindow>();
    }

    void GLRenderer::render(const ObjectList &objectList) {
        glClearColor(0.8f, 0.2f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
}
