#ifndef MODEL_H
#define MODEL_H

#include "blmesh.h"
#include "bltexture.h"

#include <memory>

#include <QOpenGLTexture>

namespace black {

/**
 * @brief The Model class
 * Model is a mesh plus texture plus model matrix
 * and a couple of different things such as
 * animations, materials and more.
 *
 * Model class make it easier to render mesh and texture
 * providing very useful method render() to draw whole model
 * using opengl pipeline
 *
 * @author george popoff <popoff96@live.com>
 *
 * @version 1.0 19.03.2017
 *  Working version of Model class
 */
class Model : public Resource
{
    friend class ResourceManager;
public:
    Model();
    Model(std::shared_ptr<Mesh> mesh);

    ~Model();

    // Resource interface
    std::shared_ptr<Texture> texture() const;
    std::shared_ptr<Mesh> mesh() const;

    void setTexture(const std::shared_ptr<Texture> &texture);
    void setMesh(const std::shared_ptr<Mesh> &mesh);

    void render();

    QMatrix4x4 getModelMatrix();

    /* MODEL matrix properties */
    void setPosition(float dx, float dy, float dz);
    void setPositionX(float dx);
    void setPositionY(float dy);
    void setPositionZ(float dz);

    void setRotation(float angleX, float angleY, float angleZ);
    void setRotationX(float angle);
    void setRotationY(float angle);
    void setRotationZ(float angle);

    void setScale(float dx, float dy, float dz);
    void setScaleX(float dx);
    void setScaleY(float dy);
    void setScaleZ(float dz);

    QVector3D position() const;
    QVector3D scale() const;
    QVector3D rotation() const;

private:
    void load(string file) override;

private:
    std::shared_ptr<Texture> m_texture;
    std::shared_ptr<Mesh> m_mesh;

    QVector3D m_position;
    QVector3D m_scale;
    QVector3D m_rotation;

    QMatrix4x4 m_matModel;

    bool m_needUpdate;
};

} // end of black namespace
#endif // MODEL_H
