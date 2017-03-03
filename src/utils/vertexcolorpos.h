#ifndef VERTEXCOLORPOS_H
#define VERTEXCOLORPOS_H

#include "vertexpos.h"

#include <QVector4D>

namespace black {

/**
 * @brief Color and position vertex
 *
 * @author <popoff96@live.com> george popoff
 * @date   03.03.2017
 */
class VertexColorPos : public VertexPos
{
public:
    VertexColorPos();
    VertexColorPos(float r, float g, float b, float a);
    VertexColorPos(const QVector4D &color);

    // Getters

    /* Position */
    float getR() const { return m_r; }
    float getG() const { return m_g; }
    float getB() const { return m_b; }
    float getA() const { return m_a; }
    QVector4D getPosition() const;

    // Setters

    /* Position */
    void setR(float r) { m_r = r; }
    void setG(float g) { m_g = g; }
    void setB(float b) { m_b = b; }
    void setA(float a) { m_a = a; }
    void setColor(float r, float g, float b, float a);
    void setColor(const QVector4D &color);

private:
    float m_r = 0.0f;
    float m_g = 0.0f;
    float m_b = 0.0f;
    float m_a = 0.0f;
};

}
#endif // VERTEXCOLORPOS_H
