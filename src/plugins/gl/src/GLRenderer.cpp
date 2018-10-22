//
// Created by popof on 09.10.2018.
//

#include "GLRenderer.h"
#include "GLSLShader.h"
#include "OpenGLRenderSystem.h"

namespace black {

    void GLRenderer::setCurrentRenderTarget(std::shared_ptr<RenderTargetInterface> target) {
        this->currentTarget = target;
    }

    void GLRenderer::render(std::shared_ptr<Mesh> mesh) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        auto lastError = glGetError();

        if (lastError != GL_NO_ERROR) {
            this->logger->critical("OpenGL error: {0}", OpenGLRenderSystem::getErrorString(lastError));
        }

        // Make the diffuse shader current
        this->diffuseShader->use();

        mesh->bind();

        glDrawArrays(mesh->getDrawMode(), 0, static_cast<GLsizei>(mesh->getVerticesCount()));
    }

    void GLRenderer::setViewPort(int x, int y, int width, int height) {
        glViewport(x, y, width, height);
    }

    GLRenderer::GLRenderer()
        : currentTarget() {

        this->logger = Logger::Get("GLRenderer");

        try {
            createShaders();
        } catch(const Exception &e) {
            logger->critical("Failed to create shader programs: " + e.getMessage());
            throw RendererInitializationException("Failed to compile shaders: " + e.getMessage());
        }
    }

    void GLRenderer::createShaders() {
        auto vertexShader = std::make_shared<GLSLShader>(GLSLShader::SimpleVertex, Shader::Type::VERTEX);
        auto fragmentShader = std::make_shared<GLSLShader>(GLSLShader::SimpleFragment, Shader::Type::FRAGMENT);

        vertexShader->compile();
        fragmentShader->compile();

        this->diffuseShader = std::make_shared<GLSLShaderProgram>();
        this->diffuseShader->setFragmentShader(fragmentShader);
        this->diffuseShader->setVertexShader(vertexShader);
        this->diffuseShader->link();
    }
}