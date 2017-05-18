#include <blmesh.h>
#include <blrenderer.h>

#include <src/utils/blobjparser.h>
#include <src/core/blconstants.h>

#include <iostream>

namespace black {

Mesh::Mesh()
    : m_isDataProvided(),
      m_isIndexProvided(),
      m_vertexCount(),
      m_vao(),
      m_positionVBO(QOpenGLBuffer::VertexBuffer),
      m_indexVBO(QOpenGLBuffer::IndexBuffer),
      m_textureVBO(QOpenGLBuffer::VertexBuffer),
      m_normalVBO(QOpenGLBuffer::VertexBuffer)
{
    auto& functions = Renderer::getInstance();

    m_vao = new QOpenGLVertexArrayObject();

    if ( !m_vao->create() ) {
        throw NotSupportedException("Vertex Array Objects");
    }

    m_vao->bind();

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
}


Mesh::Mesh(const std::vector<GLfloat> &position,
           const std::vector<GLclampf> &textureCoords)
    : Mesh()
{
    setPositionData(position);
    setTextureCoords(textureCoords);
}

Mesh::Mesh(const Mesh &mesh)
{
    this->m_vao = mesh.m_vao;
    this->m_positionVBO = mesh.m_positionVBO;
    this->m_indexVBO = mesh.m_indexVBO;
    this->m_normalVBO = mesh.m_normalVBO;
    this->m_textureVBO = mesh.m_textureVBO;
    this->m_isDataProvided = mesh.m_isDataProvided;
    this->m_isIndexProvided = mesh.m_isIndexProvided;
    this->m_vertexCount = mesh.m_vertexCount;
}

void Mesh::setPositionData(const std::vector<GLfloat> &position)
{
    auto &renderer = Renderer::getInstance();

    m_vao->bind();

    if ( !m_isIndexProvided ) {
        m_vertexCount = position.size() / 3;
    }

    if ( !m_positionVBO.bind() ) {
        throw NotSupportedException("Vertex Buffer");
    }

    m_positionVBO.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_positionVBO.allocate(position.data(),
                        position.size() * sizeof(GLfloat));

    renderer.glEnableVertexAttribArray(Constants::VERTEX_ATTR_POSITION);
    renderer.glVertexAttribPointer(Constants::VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_TRUE, 0, 0);

    m_positionVBO.release();
    m_vao->release();

    m_isDataProvided = true;
}

void Mesh::setIndexData(const std::vector<GLuint> &index)
{
    m_vao->bind();

    if ( !m_indexVBO.bind() ) {
        throw NotSupportedException("Index buffer");
    }

    m_isIndexProvided = true;
    m_vertexCount = index.size();

    m_indexVBO.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_indexVBO.allocate(index.data(),
                        m_vertexCount * sizeof(GLuint));

    m_indexVBO.release();
    m_vao->release();
}

void Mesh::setTextureCoords(const std::vector<GLclampf> &coords)
{
    auto &renderer = Renderer::getInstance();

    m_vao->bind();

    if ( !m_textureVBO.bind() ) {
        throw NotSupportedException("Vertex Buffer");
    }

    m_textureVBO.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_textureVBO.allocate(coords.data(),
                        coords.size() * sizeof(GLclampf));

    renderer.glEnableVertexAttribArray(Constants::VERTEX_ATTR_TEXCOORDS);
    renderer.glVertexAttribPointer(Constants::VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_TRUE, 0, 0);

    m_textureVBO.release();
    m_vao->release();
}

void Mesh::setNormalData(const std::vector<float> &normals)
{
    auto &renderer = Renderer::getInstance();

    m_vao->bind();

    if ( !m_normalVBO.bind() ) {
        throw NotSupportedException("Vertex Buffer");
    }

    m_normalVBO.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_normalVBO.allocate(normals.data(),
                        normals.size() * sizeof(float));

    renderer.glEnableVertexAttribArray(Constants::VERTEX_ATTR_NORMAL);
    renderer.glVertexAttribPointer(Constants::VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, 0);

    m_normalVBO.release();
    m_vao->release();
}

void Mesh::bind()
{
    m_vao->bind();
    m_indexVBO.bind();
}

void Mesh::release()
{
    m_indexVBO.release();
    m_vao->release();
}

Mesh::~Mesh()
{
}

} // end of black namespace
