#include "vertexcolorpos.h"

namespace black {

VertexColorPos::VertexColorPos()
{

}

VertexColorPos::VertexColorPos(float r, float g, float b, float a)
    : m_r(r), m_g(g), m_b(b), m_a(a)
{

}

VertexColorPos::VertexColorPos(const QVector4D &color)
    : m_r(color.x()), m_g(color.y()),
      m_b(color.z()), m_a(color.w())
{

}

QVector4D VertexColorPos::getPosition() const
{
    return QVector4D(m_r, m_g, m_b, m_a);
}

void VertexColorPos::setColor(float r, float g, float b, float a)
{
    m_r = r;
    m_g = g;
    m_b = b;
    m_a = a;
}

void VertexColorPos::setColor(const QVector4D &color)
{
    m_r = color.x();
    m_g = color.y();
    m_b = color.z();
    m_a = color.w();
}

} // end of black namespace
