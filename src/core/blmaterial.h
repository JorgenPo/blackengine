#ifndef BLMATERIAL_H
#define BLMATERIAL_H

#include <blresourcemanager.h>

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
    Material(const QVector3D &ambient,
             const QVector3D &diffuse,
             const QVector3D &spectacular,
             float shineFactor);

    Material(std::string file);

    QVector3D ambient() const;
    QVector3D diffuse() const;
    QVector3D spectacular() const;
    float shineFactor() const;

    void setAmbient(const QVector3D &ambient);
    void setDiffuse(const QVector3D &diffuse);
    void setSpectacular(const QVector3D &spectacular);
    void setShineFactor(float shineFactor);

private:
    // Resource interface
    void load(string file) override;

private:
    QVector3D m_ambient;
    QVector3D m_diffuse;
    QVector3D m_spectacular;
    float m_shineFactor;

};

} // end of black namespace
#endif // BLMATERIAL_H
