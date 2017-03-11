#include "mesh.h"
#include "GL/gl.h"

namespace black {

Mesh::Mesh(QOpenGLShaderProgram *program)
    : m_vertexCount(),
      m_vao(),
      m_positionVBO(QOpenGLBuffer::VertexBuffer),
      m_indexVBO(QOpenGLBuffer::IndexBuffer),
      m_colorVBO(QOpenGLBuffer::VertexBuffer),
      m_program(program)
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
}

Mesh::Mesh(QOpenGLShaderProgram *program,
           const std::vector<GLfloat> &position,
           const std::vector<GLuint> &index,
           const std::vector<GLclampf> &color)
    : Mesh(program)
{
    setIndexData(index);
    setPositionData(position);
    setColorData(color);
}

void Mesh::setPositionData(const std::vector<GLfloat> &position)
{
    m_program->bind();
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

    // That's hardcode... Need to manage with this
    m_program->enableAttributeArray(0);
    m_program->setAttributeBuffer(0, GL_FLOAT, 0, 3);

    m_positionVBO.release();
    m_vao.release();
    m_program->release();

    m_isDataProvided = true;
}

void Mesh::setIndexData(const std::vector<GLuint> &index)
{
    m_program->bind();
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
    m_program->release();
}

void Mesh::setColorData(const std::vector<GLclampf> &color)
{
    m_program->bind();
    m_vao.bind();

    if ( !m_colorVBO.bind() ) {
        throw NotSupportedException("Vertex Buffer");
    }

    m_colorVBO.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_colorVBO.allocate(color.data(),
                        color.size() * sizeof(GLclampf));

    // That's hardcode... Need to manage with this
    m_program->enableAttributeArray(1);
    m_program->setAttributeBuffer(1, GL_FLOAT, 0, 3);

    m_colorVBO.release();
    m_vao.release();
    m_program->release();
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
}

}
