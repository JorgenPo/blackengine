//
// Created by popof on 22.04.2018.
//

#include "GLMesh.h"

namespace black::render {
    const GLuint GLMesh::POSITION_LAYOUT = 0;

    GLMesh::GLMesh(std::vector<float> vertices) : Mesh(std::move(vertices)) {
        glGenBuffers(1, &this->vbo);
        glGenVertexArrays(1, &this->vao);
        this->update();
    }

    GLMesh::~GLMesh() {
        glDeleteBuffers(1, &this->vbo);
    }

    void GLMesh::update() {
        this->bind();

        GLuint error = glGetError();
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        error = glGetError();
        glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(float), this->vertices.data(), GL_STATIC_DRAW);
        error = glGetError();
        // Describe buffer data
        glVertexAttribPointer(POSITION_LAYOUT, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        error = glGetError();
        glEnableVertexAttribArray(POSITION_LAYOUT);
        error = glGetError();

        this->unbind();
    }

    void GLMesh::bind() {
        glBindVertexArray(this->vbo);
    }

    void GLMesh::unbind() {
        glBindVertexArray(0);
    }

}