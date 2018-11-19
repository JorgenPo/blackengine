//
// Created by popof on 09.10.2018.
//

#include "GLMesh.h"

namespace black {

    void GLMesh::bind() {
        glBindVertexArray(this->vao);
    }

    GLMesh::GLMesh(std::vector<float> vertices, std::vector<float> textureCoords)
        : Mesh(std::move(vertices), std::move(textureCoords)) {

        glGenBuffers(1, &this->positionVbo);
        glGenBuffers(1, &this->textureVbo);
        glGenVertexArrays(1, &this->vao);

        createMesh();
    }

    void GLMesh::createMesh() {
        glBindVertexArray(this->vao);

        // Vertices
        glBindBuffer(GL_ARRAY_BUFFER, this->positionVbo);
        glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(float), this->vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, this->polygonSize, GL_FLOAT, GL_FALSE, this->polygonSize * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);

        // Texture coords
        glBindBuffer(GL_ARRAY_BUFFER, this->textureVbo);
        glBufferData(GL_ARRAY_BUFFER, this->textureCoords.size() * sizeof(float), this->textureCoords.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
        glEnableVertexAttribArray(1);
    }

    int GLMesh::getDrawMode() const {
        switch(this->drawMode) {
            case DrawMode::POINTS:
                return GL_POINTS;
            case DrawMode::LINES:
                return GL_LINES;
            case DrawMode::LINE_LOOP:
                return GL_LINE_LOOP;
            case DrawMode::LINE_STRIP:
                return GL_LINE_STRIP;
            case DrawMode::TRIANGLE_STRIP:
                return GL_TRIANGLE_STRIP;
            case DrawMode::TRIANGLE_FAN:
                return GL_TRIANGLE_FAN;
            case DrawMode::TRIANGLES:
                return GL_TRIANGLES;

                // Unimplemented
            case DrawMode::QUAD_STRIP:
            case DrawMode::QUADS:
            case DrawMode::POLYGON:
                return GL_POINTS;
        }
    }
}