#include "bllight.h"

namespace black {

Light::Light()
    : m_position(),
      m_color()
{

}

Light::Light(std::array<float, 3> lightPos,
             std::array<float, 3> lightColor)
    : m_position(lightPos[0], lightPos[1], lightPos[2]),
      m_color(lightColor[0], lightColor[1], lightColor[2])
{

}

QVector3D Light::position() const
{
    return m_position;
}

void Light::setPosition(const QVector3D &position)
{
    m_position = position;
}

QVector3D Light::color() const
{
    return m_color;
}

void Light::setColor(const QVector3D &color)
{
    m_color = color;
}

}
