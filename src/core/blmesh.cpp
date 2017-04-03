#include "blmesh.h"

#include <src/utils/blobjparser.h>
#include <src/core/blconstants.h>

#include <iostream>

namespace black {

Mesh::Mesh()
    : m_vertexCount(),
      m_vao(),
      m_positionVBO(QOpenGLBuffer::VertexBuffer),
      m_indexVBO(QOpenGLBuffer::IndexBuffer),
      m_textureVBO(QOpenGLBuffer::VertexBuffer),
      m_normalVBO(QOpenGLBuffer::VertexBuffer),
      m_program()
{
    if ( !m_vao.create() ) {
        throw NotSupportedException("Vertex Array Objects");
    }

    m_vao.bind();

    if ( !m_positionVBO.create() ) {
        throw NotSupportedException("OpenGL buffers");
    }

    if ( !m_indexVBO.create() ) {
        throw NotSupportedException("OpenGL buffers");
    }

    if ( !m_textureVBO.create() ) {
        throw NotSupportedException("OpenGL buffers");
    }

    if ( !m_normalVBO.create() ) {
        throw NotSupportedException("OpenGL buffers");
    }

    initializeOpenGLFunctions();
}


Mesh::Mesh(const std::vector<GLfloat> &position,
           const std::vector<GLclampf> &textureCoords)
    : Mesh()
{
    setPositionData(position);
    setTextureCoords(textureCoords);
}

void Mesh::setPositionData(const std::vector<GLfloat> &position)
{
    m_vao.bind();

    if ( !m_isIndexProvided ) {
        m_vertexCount = position.size() / 3;
    }

    if ( !m_positionVBO.bind() ) {
        throw NotSupportedException("Vertex Buffer");
    }

    m_positionVBO.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_positionVBO.allocate(position.data(),
                        position.size() * sizeof(GLfloat));

    glEnableVertexAttribArray(Constants::VERTEX_ATTR_POSITION);
    glVertexAttribPointer(Constants::VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_TRUE, 0, 0);

    m_positionVBO.release();
    m_vao.release();

    m_isDataProvided = true;
}

void Mesh::setIndexData(const std::vector<GLuint> &index)
{
    m_vao.bind();

    if ( !m_indexVBO.bind() ) {
        throw NotSupportedException("Index buffer");
    }

    m_isIndexProvided = true;
    m_vertexCount = index.size();

    m_indexVBO.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_indexVBO.allocate(index.data(),
                        m_vertexCount * sizeof(GLuint));

    m_indexVBO.release();
    m_vao.release();
}

void Mesh::setTextureCoords(const std::vector<GLclampf> &coords)
{
    m_vao.bind();

    if ( !m_textureVBO.bind() ) {
        throw NotSupportedException("Vertex Buffer");
    }

    m_textureVBO.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_textureVBO.allocate(coords.data(),
                        coords.size() * sizeof(GLclampf));

    glEnableVertexAttribArray(Constants::VERTEX_ATTR_TEXCOORDS);
    glVertexAttribPointer(Constants::VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_TRUE, 0, 0);

    m_textureVBO.release();
    m_vao.release();
}

void Mesh::setNormalData(const std::vector<float> &normals)
{
    m_vao.bind();

    if ( !m_normalVBO.bind() ) {
        throw NotSupportedException("Vertex Buffer");
    }

    m_normalVBO.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_normalVBO.allocate(normals.data(),
                        normals.size() * sizeof(float));

    glEnableVertexAttribArray(Constants::VERTEX_ATTR_NORMAL);
    glVertexAttribPointer(Constants::VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, 0);

    m_normalVBO.release();
    m_vao.release();
}

void Mesh::bind()
{
    m_vao.bind();
    m_indexVBO.bind();
}

void Mesh::release()
{
    m_indexVBO.release();
    m_vao.release();
}


Mesh::~Mesh()
{
    m_vao.destroy();
    m_positionVBO.destroy();
    m_indexVBO.destroy();
    m_textureVBO.destroy();
    m_normalVBO.destroy();
}

} // end of black namespace
