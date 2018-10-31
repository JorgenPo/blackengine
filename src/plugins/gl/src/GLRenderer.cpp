//
// Created by popof on 09.10.2018.
//

#include "GLRenderer.h"
#include "GLSLShader.h"
#include "OpenGLRenderSystem.h"

namespace black {

    void GLRenderer::setCurrentRenderTarget(std::shared_ptr<RenderTargetInterface> target) {
        this->currentTarget = target;

        this->projection = glm::perspective(glm::radians(45.0f), this->currentTarget->getRenderTargetAspectRatio(), 0.1f, 100.0f);
        this->view = glm::translate(this->view, glm::vec3(0.0f, 0.0f, -3.0f));
    }

    void GLRenderer::render(std::shared_ptr<Model> model, glm::mat4 modelMatrix) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        auto lastError = glGetError();

        if (lastError != GL_NO_ERROR) {
            this->logger->critical("OpenGL error: {0}", OpenGLRenderSystem::getErrorString(lastError));
        }

        // Make the diffuse shader current
        this->diffuseShader->use();

        this->diffuseShader->setUniformVariable("model", modelMatrix);
        this->diffuseShader->setUniformVariable("view", this->view);
        this->diffuseShader->setUniformVariable("projection", this->projection);

        std::for_each(model->getParts().begin(), model->getParts().end(), [](const auto &part) {
            glDrawArrays(static_cast<GLenum>(part.mesh->getDrawMode()), 0, static_cast<GLsizei>(part.mesh->getVerticesCount()));
        });
    }

    void GLRenderer::setViewPort(int x, int y, int width, int height) {
        glViewport(x, y, width, height);
    }

    GLRenderer::GLRenderer()
        : currentTarget(), model(1.0f), view(1.0f), projection(1.0f) {

        this->logger = Logger::Get("GLRenderer");

        //this->projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);

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