//
// Created by popof on 22.04.2018.
//

#include "GLMesh.h"

namespace black::render {
    const GLuint GLMesh::POSITION_LAYOUT = 0;
    const GLuint GLMesh::TEXCOORD_LAYOUT = 1;

    GLMesh::GLMesh(std::vector<float> vertices, std::vector<unsigned int> indices, std::vector<float> textureCoords)
            : Mesh(std::move(vertices), std::move(indices), std::move(textureCoords)) {
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

        // All vertex data in one buffer
        std::vector<float> data;
        data.insert(data.end(), this->vertices.begin(), this->vertices.end());
        data.insert(data.end(), this->textureCoords.begin(), this->textureCoords.end());

        // Vertices
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);

        // Indices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), this->indices.data(), GL_STATIC_DRAW);

        // Describe buffer data
        glVertexAttribPointer(POSITION_LAYOUT, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glVertexAttribPointer(TEXCOORD_LAYOUT, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), reinterpret_cast<void*>(this->vertices.size() * sizeof(float)));

        glEnableVertexAttribArray(POSITION_LAYOUT);
        glEnableVertexAttribArray(TEXCOORD_LAYOUT);

        this->unbind();
    }

    void GLMesh::bind() {
        glBindVertexArray(this->vbo);
    }

    void GLMesh::unbind() {
        glBindVertexArray(0);
    }

}