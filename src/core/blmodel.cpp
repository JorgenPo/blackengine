#include "blmodel.h"

#include <blobjparser.h>
#include <src/utils/bllogger.h>
#include <blfileexceptions.h>

#include <iostream>

namespace black {

Model::Model()
    : m_mesh(),
      m_position(), m_scale(1, 1, 1),
      m_rotation(), m_matModel(),
      m_needUpdate(), m_initialized()
{
    auto& rm = ResourceManager::getInstance();

    initializeOpenGLFunctions();

    m_material = rm.get<Material>("materials/default.mtl");
}

Model::Model(std::string file)
    : Model()
{
    load(file);
}

Model::~Model()
{
    m_material.reset();
}

void Model::load(string file)
{
    Logger::getInstance() << "Loading " << file << " model..." << std::endl;
    OBJParser parser;

    try {
        parser.parse(file);

        m_mesh = std::make_unique<Mesh>();
        m_mesh->setPositionData(parser.positions());

        if ( parser.indicesCount() != 0 ) {
            m_mesh->setIndexData(parser.indices());
        }

        if ( parser.hasTexture() ) {
            m_mesh->setTextureCoords(parser.texCoordinates());
        }

        m_mesh->setNormalData(parser.normals());

    } catch(std::string e) {
        throw ParseException(file, e);
    }

    m_initialized = true;

    auto &rm = ResourceManager::getInstance();

    // Get mesh material
    m_material = std::make_shared<Material>();
    m_material = rm.get<Material>( m_material->folderName() + "/" + parser.matFile() );

    Logger::getInstance() << " Done! " << std::endl;
}

void Model::setScale(float scaleX, float scaleY, float scaleZ)
{
    m_needUpdate = true;
    m_scale.setX(scaleX);
    m_scale.setY(scaleY);
    m_scale.setZ(scaleZ);
}

void Model::setScale(float scale)
{
    this->setScale(scale, scale, scale);
}

QVector3D Model::position() const
{
    return m_position;
}

QVector3D Model::scale() const
{
    return m_scale;
}

QVector3D Model::rotation() const
{
    return m_rotation;
}

std::shared_ptr<Material> Model::material() const
{
    return m_material;
}

void Model::render()
{
    if ( !m_initialized ) {
        Logger::getInstance("error") << "Trying to render empty model "
                                     << "(no mesh provided)" << std::endl;
        return;
    }

    m_mesh->bind();

    if ( m_material->texture() != nullptr ) {
        m_material->texture()->bind();
    }

    if ( m_mesh->isIndexed() ) {
        glDrawElements(GL_TRIANGLES, m_mesh->vertexCount(), GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(GL_TRIANGLES, 0, m_mesh->vertexCount());
    }

    if ( m_material->texture() != nullptr ) {
        m_material->texture()->release();
    }

    m_mesh->release();
}

QMatrix4x4 Model::modelMatrix()
{
    if ( m_needUpdate ) {
        m_matModel.setToIdentity();
        m_matModel.translate(m_position);
        m_matModel.rotate(m_rotation.x(), 1.0f, 0.0f, 0.0f);
        m_matModel.rotate(m_rotation.y(), 0.0f, 1.0f, 0.0f);
        m_matModel.rotate(m_rotation.z(), 0.0f, 0.0f, 1.0f);
        m_matModel.scale(m_scale);

        m_needUpdate = false;
    }

    return m_matModel;
}

void Model::setPosition(float dx, float dy, float dz)
{
    m_position.setX(dx);
    m_position.setY(dy);
    m_position.setZ(dz);
    m_needUpdate = true;
}

void Model::setPositionX(float dx)
{
    m_position.setX(dx);
    m_needUpdate = true;
}

void Model::setPositionY(float dy)
{
    m_position.setY(dy);
    m_needUpdate = true;
}

void Model::setPositionZ(float dz)
{
    m_position.setZ(dz);
    m_needUpdate = true;
}

void Model::setRotation(float angleX, float angleY, float angleZ)
{
    m_rotation.setX(angleX);
    m_rotation.setY(angleY);
    m_rotation.setZ(angleZ);
    m_needUpdate = true;
}

void Model::setRotationX(float angle)
{
    m_rotation.setX(angle);
    m_needUpdate = true;
}

void Model::setRotationY(float angle)
{
    m_rotation.setY(angle);
    m_needUpdate = true;
}

void Model::setRotationZ(float angle)
{
    m_rotation.setZ(angle);
    m_needUpdate = true;
}

void Model::setScaleX(float dx)
{
    m_scale.setX(dx);
    m_needUpdate = true;
}

void Model::setScaleY(float dy)
{
    m_scale.setY(dy);
    m_needUpdate = true;
}

void Model::setScaleZ(float dz)
{
    m_scale.setZ(dz);
    m_needUpdate = true;
}

std::shared_ptr<Texture> Model::texture() const
{
    return m_material->texture();
}

void Model::setTexture(const std::shared_ptr<Texture> &texture)
{
    m_material->setTexture(texture);
}


} // end of black namespace
