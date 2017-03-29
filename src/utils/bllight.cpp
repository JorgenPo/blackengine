#include "bllight.h"

namespace black {

Light::Light()
    : m_position(0, 10.0f, 0),
      m_ambient(0.1f, 0.1f, 0.1f),
      m_diffuse(0.8f, 0.8f, 0.8f),
      m_spectacular(1.0f, 1.0f, 1.0f)
{

}

Light::Light(const QVector3D& lightPos,
             const QVector3D& ambient,
             const QVector3D& diffuse,
             const QVector3D& spectacular)
    : m_position(lightPos), m_ambient(ambient),
      m_diffuse(diffuse), m_spectacular(spectacular)
{

}

QVector3D Light::position() const
{
    return m_position;
}

QVector3D Light::ambient() const
{
    return m_ambient;
}

QVector3D Light::diffuse() const
{
    return m_diffuse;
}

QVector3D Light::spectacular() const
{
    return m_spectacular;
}

void Light::setPosition(const QVector3D &position)
{
    m_position = position;
}

void Light::setAmbient(const QVector3D &ambient)
{
    m_ambient = ambient;
}

void Light::setDiffuse(const QVector3D &diffuse)
{
    m_diffuse = diffuse;
}

void Light::setSpectacular(const QVector3D &spectacular)
{
    m_spectacular = spectacular;
}


}
