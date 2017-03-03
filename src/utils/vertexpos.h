#ifndef VERTEXPOS_H
#define VERTEXPOS_H

#include "ivertex.h"

#include <QVector3D>

namespace black {

/**
 * @brief Simple position vector
 *  Contains 3D coordinates.
 *
 * @author <popoff96@live.com> george popoff
 * @date   02.03.2017
 */
class VertexPos : public IVertex
{

public:
    VertexPos();
    VertexPos(float x, float y, float z = 0.0f);
    VertexPos(const QVector3D &point);

    // Getters

    /* Position */
    float getX() const { return m_x; }
    float getY() const { return m_y; }
    float getZ() const { return m_z; }
    QVector3D getPosition() const;

    // Setters

    /* Position */
    void setX(float x) { m_x = x; }
    void setY(float y) { m_y = y; }
    void setZ(float z) { m_z = z; }
    void setPosition(const QVector3D &point);

private:
    float m_x = 0.0f;
    float m_y = 0.0f;
    float m_z = 0.0f;
};

} // end of black namespace

#endif // VERTEXPOS_H
