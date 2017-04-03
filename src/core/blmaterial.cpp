#include "blmaterial.h"

#include <blmtlparser.h>
#include <src/utils/bllogger.h>

namespace black {

Material::Material()
    : m_ambient(), m_diffuse(), m_spectacular(),
      m_shineFactor(0.5), m_texture()
{

}

Material::Material(const std::shared_ptr<Texture> &texture,
                   const QVector3D &ambient,
                   const QVector3D &diffuse,
                   const QVector3D &spectacular,
                   float shineFactor)
    : m_ambient(ambient), m_diffuse(diffuse),
      m_spectacular(spectacular), m_shineFactor(shineFactor),
      m_texture(texture)
{

}

Material::Material(std::string file)
{
    load(file);
}


QVector3D Material::ambient() const
{
    return m_ambient;
}

QVector3D Material::diffuse() const
{
    return m_diffuse;
}

QVector3D Material::spectacular() const
{
    return m_spectacular;
}

void Material::setAmbient(const QVector3D &ambient)
{
    m_ambient = ambient;
}

void Material::setDiffuse(const QVector3D &diffuse)
{
    m_diffuse = diffuse;
}

void Material::setSpectacular(const QVector3D &spectacular)
{
    m_spectacular = spectacular;
}

void Material::load(string file)
{
    Logger::getInstance() << "Loading " << file << " material...";

    MtlParser parser;
    parser.parse(file);

    // TODO: find a way to work with a bunch of materials
    m_ambient = parser.getAmbient();
    m_diffuse = parser.getDiffuse();
    m_spectacular = parser.getSpectacular();
    m_shineFactor = parser.getShineFactor();
    m_texture = parser.getTexture();

    Logger::getInstance() << " Done! " << std::endl;
}

std::shared_ptr<Texture> Material::texture() const
{
    return m_texture;
}

void Material::setTexture(const std::shared_ptr<Texture> &texture)
{
    m_texture = texture;
}

float Material::shineFactor() const
{
    return m_shineFactor;
}

void Material::setShineFactor(float shineFactor)
{
    m_shineFactor = shineFactor;
}

} // end of black namespace
