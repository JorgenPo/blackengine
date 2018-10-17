//
// Created by popof on 09.10.2018.
//

#include "GLRenderer.h"

namespace black {

    void GLRenderer::setCurrentRenderTarget(std::shared_ptr<RenderTargetInterface> target) {
        this->currentTarget = target;
    }

    void GLRenderer::render(std::shared_ptr<Mesh> mesh) {
        glClear(GL_COLOR_BUFFER_BIT);

        mesh->bind();
        glDrawArrays(static_cast<GLenum>(mesh->getDrawMode()), 0, static_cast<GLsizei>(mesh->getVerticesCount()));
    }

    void GLRenderer::setViewPort(int x, int y, int width, int height) {
        glViewport(x, y, width, height);
    }

    GLRenderer::GLRenderer()
        : currentTarget() {

    }
}