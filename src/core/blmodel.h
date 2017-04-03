#ifndef MODEL_H
#define MODEL_H

#include <src/core/blmaterial.h>
#include <src/core/blmesh.h>
#include <src/core/bltexture.h>

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
 * @version 1.2.5 02.04.2017
 *
 * @version 1.2 28.03.2017
 * Support of materials. Loading from obj code
 * moved from mesh to model class
 *
 * @version 1.1 27.03.2017
 *  Fixed bug with scale vector
 *
 * @version 1.0 19.03.2017
 *  Working version of Model class
 */
class Model : public Resource, private QOpenGLFunctions
{
public:

    friend class ResourceManager;
public:
    Model();
    Model(std::string file);

    ~Model();

    // Resource interface
    std::shared_ptr<Texture> texture() const;
    std::shared_ptr<Material> material() const;

    void setTexture(const std::shared_ptr<Texture> &texture);

    void render();

    QMatrix4x4 modelMatrix();

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
    void setScale(float scale);
    void setScaleX(float dx);
    void setScaleY(float dy);
    void setScaleZ(float dz);

    QVector3D position() const;
    QVector3D scale() const;
    QVector3D rotation() const;

private:
    void load(string file) override;
public:
    std::string defaultName() override { return std::string("default.obj"); }
    std::string folderName()  override { return std::string("models");      }

private:
    std::unique_ptr<Mesh> m_mesh;
    std::shared_ptr<Material> m_material;

    QVector3D m_position;
    QVector3D m_scale;
    QVector3D m_rotation;

    QMatrix4x4 m_matModel;

    bool m_needUpdate;
    bool m_initialized;
};

} // end of black namespace
#endif // MODEL_H
