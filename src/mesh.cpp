#include "mesh.h"
#include "GL/gl.h"

namespace black {

Mesh::Mesh(QOpenGLShaderProgram *program)
    : m_vao(),
      m_positionVBO(QOpenGLBuffer::VertexBuffer),
      m_position(),
      m_program(program)
{
    if ( !m_vao.create() ) {
        throw NotSupportedException("Vertex Array Objects");
    }

    m_vao.bind();

    if ( !m_positionVBO.create() ) {
        throw NotSupportedException("OpenGL buffers");
    }
}

Mesh::Mesh(QOpenGLShaderProgram *program, const std::vector<float> &position)
    : Mesh(program)
{
    setPositionData(position);
}

void Mesh::setPositionData(const std::vector<float> &position)
{
    m_position = position;

    m_program->bind();

    m_vao.bind();

    if ( !m_positionVBO.bind() ) {
        throw NotSupportedException("Vertex Buffer");
    }

    m_positionVBO.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_positionVBO.allocate(m_position.data(),
                        m_position.size() * sizeof(float));

    // That's hardcode... Need to manage with this
    m_program->enableAttributeArray(0);
    m_program->setAttributeBuffer(0, GL_FLOAT, 0, 3);

    m_positionVBO.release();
    m_vao.release();
    m_program->release();

    m_isDataProvided = true;
}

void Mesh::render(int primitive, int offset, int count)
{
    bind();

    if ( !m_isDataProvided ) {
        throw NoDataProvidedException();
    }

    if ( count < 0 ) {
        count = m_position.size() / 3;
    }

    glDrawArrays(primitive, offset, count);

    release();
}

void Mesh::bind()
{
    m_vao.bind();
}

void Mesh::release()
{
    m_vao.release();
}


Mesh::~Mesh()
{
    // Destoy vao, release data
    // TODO: maybe remove this? destructor of Qt object
    //  do this.
    m_vao.destroy();
    m_positionVBO.destroy();
}

}
