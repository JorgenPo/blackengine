#include "blmtlparser.h"

#include <bllogger.h>
#include <blfileexceptions.h>
#include <map>

namespace black {

MtlParser::MtlParser()
    : m_file(), m_materials()
{

}

void MtlParser::parse(std::string file)
{
    if ( m_file.is_open() ) {
        m_file.close();
    }

    m_file.open(file);

    if ( !m_file.is_open() ) {
        throw NoSuchFileException(file);
    }

    std::string line;

    // First file header
    getline(m_file, line);

    if ( line.find("MTL") == std::string::npos ) {
        throw WrongFileException(file, ".mtl");
    }

    // Second header. Contains materials count
    m_file >> line; // #
    m_file >> line; // Material
    m_file >> line; // Count:

    int count = 0;
    m_file >> count;

    if ( count == 0 ) {
        throw ParseException(file, "No materials was found in this file!");
    }

    QVector3D ambient;
    QVector3D diffuse;
    QVector3D spectacular;
    float shineFactor;

    std::string matName;
    std::string type;

    std::streampos oldpos;
    float value;
    while ( m_file >> line ) {
        while ( line != "newmtl" ) { }

        // Defaults
        auto &rm = ResourceManager::getInstance();

        std::string textureName;
        ambient = { 0, 0, 0 };
        diffuse = { 0, 0, 0 };
        spectacular = { 0, 0, 0 };
        shineFactor = 0.5f;

        // Material name
        m_file >> matName;

        oldpos = m_file.tellg();
        while ( m_file >> type ) {
            if ( type == "newmtl" ) { // Continue with next material
                m_file.seekg(oldpos);  // TODO: OPTIMIZE
                break;
            }

            if ( type == "Ns" ) {
                m_file >> value;

                shineFactor = value;
            } else if ( type == "Ka" ) {
                ambient = getVector();
            } else if ( type == "Kd" ) {
                diffuse = getVector();
            } else if ( type == "Ks" ) {
                spectacular = getVector();
            } else if ( type == "map_Kd" ) {
                m_file >> textureName;
            }

            oldpos = m_file.tellg();
        }

        std::shared_ptr<Texture> texture;
        if ( !textureName.empty() ) {
            texture = rm.get<Texture>(textureName, false);
        } else {
            texture = nullptr;
        }
        m_materials[matName] = Material(texture, ambient, diffuse, spectacular, shineFactor);

        texture.reset();
    }
}

QVector3D MtlParser::getVector()
{
    float x, y, z;

    m_file >> x;
    m_file >> y;
    m_file >> z;

    return { x, y, z };
}

std::map<std::string, Material> MtlParser::getMaterials() const
{
    return m_materials;
}

std::shared_ptr<Texture> MtlParser::getTexture() const
{
    return m_materials.begin()->second.texture();
}

QVector3D MtlParser::getAmbient() const
{
    return m_materials.begin()->second.ambient();
}

QVector3D MtlParser::getDiffuse() const
{
    return m_materials.begin()->second.diffuse();
}

QVector3D MtlParser::getSpectacular() const
{
    return m_materials.begin()->second.spectacular();
}

float MtlParser::getShineFactor() const
{
    return m_materials.begin()->second.shineFactor();
}

} // end of black namespace
