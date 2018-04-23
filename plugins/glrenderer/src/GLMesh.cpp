//
// Created by popof on 22.04.2018.
//

#include "GLMesh.h"

namespace black::render {
    const GLuint GLMesh::POSITION_LAYOUT = 0;

    GLMesh::GLMesh(std::vector<float> vertices, std::vector<unsigned int> indices)
            : Mesh(std::move(vertices), std::move(indices)) {
        glGenBuffers(1, &this->vbo);
        glGenBuffers(1, &this->ebo);
        glGenVertexArrays(1, &this->vao);
        this->update();
    }

    GLMesh::~GLMesh() {
        glDeleteBuffers(1, &this->vbo);
        glDeleteBuffers(1, &this->ebo);
        glDeleteVertexArrays(1, &this->vao);
    }

    void GLMesh::update() {
        this->bind();

        // Vertices
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(float), this->vertices.data(), GL_STATIC_DRAW);

        // Indices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), this->indices.data(), GL_STATIC_DRAW);

        // Describe buffer data
        glVertexAttribPointer(POSITION_LAYOUT, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(POSITION_LAYOUT);

        this->unbind();
    }

    void GLMesh::bind() {
        glBindVertexArray(this->vbo);
    }

    void GLMesh::unbind() {
        glBindVertexArray(0);
    }

}