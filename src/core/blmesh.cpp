#include "blmesh.h"

#include "blobjparser.h"

#include <iostream>

namespace black {

Mesh::Mesh()
    : m_vertexCount(),
      m_vao(),
      m_positionVBO(QOpenGLBuffer::VertexBuffer),
      m_indexVBO(QOpenGLBuffer::IndexBuffer),
      m_colorVBO(QOpenGLBuffer::VertexBuffer),
      m_textureVBO(QOpenGLBuffer::VertexBuffer)
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

    if ( !m_colorVBO.create() ) {
        throw NotSupportedException("OpenGL buffers");
    }

    if ( !m_textureVBO.create() ) {
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

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);

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

void Mesh::setColorData(const std::vector<GLclampf> &color)
{
    m_vao.bind();

    if ( !m_colorVBO.bind() ) {
        throw NotSupportedException("Vertex Buffer");
    }

    m_colorVBO.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_colorVBO.allocate(color.data(),
                        color.size() * sizeof(GLclampf));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

    m_colorVBO.release();
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

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, 0, 0);

    m_textureVBO.release();
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
    // Destoy vao, release data
    // TODO: maybe remove this? destructor of Qt object
    //  do this.
    m_vao.destroy();
    m_positionVBO.destroy();
    m_indexVBO.destroy();
    m_colorVBO.destroy();
    m_textureVBO.destroy();
}

// LOADING MESH FROM FILE
void Mesh::load(string file)
{
    OBJParser parser;

    try {
        parser.parseObj(file);

        this->setPositionData(parser.positions());

        if ( parser.indicesCount() != 0 ) {
            this->setIndexData(parser.indices());
        }

        this->setTextureCoords(parser.texCoordinates());
    } catch(std::string e) {
        std::cerr << "Failed to load a mesh from " << file << "!\n";
        std::cerr << "Error: " << e << '\n';
        //throw exception;
    }
}

}
