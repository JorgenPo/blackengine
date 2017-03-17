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
 * @version 1.0 First version
 *
 * @author george popoff <popoff96@live.com>
 * @date 16.03.2017
 */
class Light
{
public:
    Light();

    Light(std::array<float, 3> lightPos,
          std::array<float, 3> lightColor);

    QVector3D position() const;
    QVector3D color() const;

    void setPosition(const QVector3D &position);
    void setColor(const QVector3D &color);

private:
    QVector3D m_position;
    QVector3D m_color;
};

}
#endif // BLLIGHT_H
