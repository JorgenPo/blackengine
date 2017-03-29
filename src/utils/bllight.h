#ifndef BLLIGHT_H
#define BLLIGHT_H

#include <QVector3D>
#include <array>

namespace black {

/**
 * Light class. Represents a light like a sun
 *
 * @brief The Light object class
 *
 * @version 1.0a 29.03.2017
 * Reworked version. All components stores separetely.
 * Added shine factor.
 *
 * @version 1.0 First version
 *
 * @author george popoff <popoff96@live.com>
 * @date 16.03.2017
 */
class Light
{
public:
    Light();

    Light(const QVector3D& lightPos,
          const QVector3D& ambient,
          const QVector3D& diffuse,
          const QVector3D& spectacular);

    QVector3D position() const;
    QVector3D ambient() const;
    QVector3D diffuse() const;
    QVector3D spectacular() const;

    void setPosition(const QVector3D &position);
    void setAmbient(const QVector3D &ambient);
    void setDiffuse(const QVector3D &diffuse);
    void setSpectacular(const QVector3D &spectacular);
private:
    QVector3D m_position;
    QVector3D m_ambient;
    QVector3D m_diffuse;
    QVector3D m_spectacular;
};

}
#endif // BLLIGHT_H
