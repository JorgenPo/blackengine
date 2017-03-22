#include "blmodel.h"

#include <blobjparser.h>

namespace black {

Model::Model()
    : m_mesh(),
      m_position(), m_scale(),
      m_rotation(), m_matModel(),
      m_needUpdate()
{
    initializeOpenGLFunctions();

    m_texture = std::shared_ptr<Texture>(ResourceManager::getInstance()
            .get<Texture>("textures/default.jpg"));
}

Model::Model(std::shared_ptr<Mesh> mesh)
    : Model()
{
    m_mesh = mesh;
}

Model::~Model()
{
    m_mesh.reset();
    m_texture.reset();
}

void Model::load(string file)
{
    auto &rm = ResourceManager::getInstance();

    // Get loaded mesh or load it
    m_mesh = rm.get<Mesh>(file, false);
}

void Model::setScale(float scaleX, float scaleY, float scaleZ)
{
    m_needUpdate = true;
    m_scale.setX(scaleX);
    m_scale.setY(scaleY);
    m_scale.setZ(scaleZ);
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

std::shared_ptr<Mesh> Model::mesh() const
{
    return m_mesh;
}

void Model::setMesh(const std::shared_ptr<Mesh> &mesh)
{
    m_needUpdate = true;
    m_mesh = mesh;
}

void Model::render()
{
    m_mesh->bind();
    m_texture->bind();

    if ( m_mesh->isIndexed() ) {
        glDrawElements(GL_TRIANGLES, m_mesh->vertexCount(), GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(GL_TRIANGLES, 0, m_mesh->vertexCount());
    }

    m_texture->release();
    m_mesh->release();
}

QMatrix4x4 Model::getModelMatrix()
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
    return m_texture;
}

void Model::setTexture(const std::shared_ptr<Texture> &texture)
{
    m_texture = texture;
}


} // end of black namespace
