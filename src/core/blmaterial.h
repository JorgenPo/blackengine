#ifndef BLMATERIAL_H
#define BLMATERIAL_H

#include <src/core/blresourcemanager.h>
#include <src/core/bltexture.h>

#include <QVector3D>

namespace black {

/**
 * @brief The Material class
 * Material class represents a model of
 * real material. Contains such parameters as
 * ambient, diffuse, spectacular lightning coeffs and
 * other.
 * Can be handled by Resource Manager.
 *
 * @version 1.1 02.04.2017
 * Now materials contain textures as well.
 *
 * @version 1.0 27.03.2017
 * First working version.
 *
 * @author george popof <popoff96@live.com>
 * @resource
 */
class Material : public Resource
{
    friend class ResourceManager;
public:
    Material();
    Material(const std::shared_ptr<Texture> &texture,
             const QVector3D &ambient,
             const QVector3D &diffuse,
             const QVector3D &spectacular,
             float shineFactor);

    Material(std::string file);


    std::shared_ptr<Texture> texture() const;
    QVector3D ambient() const;
    QVector3D diffuse() const;
    QVector3D spectacular() const;
    float shineFactor() const;

    void setAmbient(const QVector3D &ambient);
    void setDiffuse(const QVector3D &diffuse);
    void setSpectacular(const QVector3D &spectacular);
    void setShineFactor(float shineFactor);
    void setTexture(const std::shared_ptr<Texture> &texture);

private:
    // Resource interface
    void load(string file) override;

public:
    std::string defaultName() override { return std::string("default.mtl"); }
    std::string folderName()  override { return std::string("materials");    }

private:
    QVector3D m_ambient;
    QVector3D m_diffuse;
    QVector3D m_spectacular;
    float m_shineFactor;

    std::shared_ptr<Texture> m_texture;
};

} // end of black namespace
#endif // BLMATERIAL_H
