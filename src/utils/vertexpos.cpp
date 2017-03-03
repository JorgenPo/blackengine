#include "vertexpos.h"

namespace black {

VertexPos::VertexPos()
{

}

VertexPos::VertexPos(float x, float y, float z)
    : m_x(x), m_y(y), m_z(z)
{

}

VertexPos::VertexPos(const QVector3D &point)
    : m_x(point.x()), m_y(point.y()), m_z(point.z())
{

}

QVector3D VertexPos::getPosition() const
{
    return QVector3D(m_x, m_y, m_z);
}

void VertexPos::setPosition(const QVector3D &point)
{
    m_x = point.x();
    m_y = point.y();
    m_z = point.z();
}

} // end of black namespace
