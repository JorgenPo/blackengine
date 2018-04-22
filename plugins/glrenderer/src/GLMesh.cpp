//
// Created by popof on 22.04.2018.
//

#include "GLMesh.h"

black::render::GLMesh::GLMesh(std::vector<float> vertices) : Mesh(std::move(vertices)) {
    glGenBuffers(1, &this->vbo);
    this->update();
}

black::render::GLMesh::~GLMesh() {
    glDeleteBuffers(1, &this->vbo);
}

void black::render::GLMesh::update() {
    this->bind();
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(float), this->vertices.data(), GL_STATIC_DRAW);
    this->unbind();
}

void black::render::GLMesh::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
}

void black::render::GLMesh::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
