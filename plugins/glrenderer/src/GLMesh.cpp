//
// Created by popof on 22.04.2018.
//

#include <core/Exception.h>
#include "GLMesh.h"

namespace black::render {
    const GLuint GLMesh::POSITION_LAYOUT = 0;
    const GLuint GLMesh::TEXCOORD_LAYOUT = 1;

    GLMesh::GLMesh() {
        glGenBuffers(1, &this->positionVbo);
        glGenBuffers(1, &this->texturesVbo);
        glGenBuffers(1, &this->ebo);
        glGenVertexArrays(1, &this->vao);
    }

    GLMesh::GLMesh(std::vector<float> vertices, std::vector<unsigned int> indices, std::vector<float> textureCoords, int polygonLength)
            : Mesh(std::move(vertices), std::move(indices), std::move(textureCoords), polygonLength) {
        glGenBuffers(1, &this->positionVbo);
        glGenBuffers(1, &this->texturesVbo);
        glGenBuffers(1, &this->ebo);
        glGenVertexArrays(1, &this->vao);
        this->update();
    }

    GLMesh::~GLMesh() {
        glDeleteBuffers(1, &this->positionVbo);
        glDeleteBuffers(1, &this->texturesVbo);
        glDeleteBuffers(1, &this->ebo);
        glDeleteVertexArrays(1, &this->vao);
    }

    void GLMesh::update() {
        this->initialized = true;

        this->bind();

        // Vertices
        glBindBuffer(GL_ARRAY_BUFFER, this->positionVbo);
        glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(float), this->vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(POSITION_LAYOUT, this->getPolygonLength(), GL_FLOAT, GL_FALSE, this->getPolygonLength() * sizeof(float), nullptr);
        glEnableVertexAttribArray(POSITION_LAYOUT);

        // Texture coords
        glBindBuffer(GL_ARRAY_BUFFER, this->texturesVbo);
        glBufferData(GL_ARRAY_BUFFER, this->textureCoords.size() * sizeof(float), this->textureCoords.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(TEXCOORD_LAYOUT, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
        glEnableVertexAttribArray(TEXCOORD_LAYOUT);

        // Indices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), this->indices.data(), GL_STATIC_DRAW);

        this->unbind();
    }

    void GLMesh::bind() {
        if (this->isInitialized()) {
            glBindVertexArray(this->vao);
        }
    }

    void GLMesh::unbind() {
        glBindVertexArray(0);
    }

    void GLMesh::draw() {
        this->bind();
        glDrawElements(GL_TRIANGLES, this->getIndicesCount(), GL_UNSIGNED_INT, nullptr);
        this->unbind();
    }

    void GLMesh::draw(int offset, int count) {
        this->bind();
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, reinterpret_cast<void *>(sizeof(unsigned int) * offset));
        this->unbind();
    }
}