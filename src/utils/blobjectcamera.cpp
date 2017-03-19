#include "blspectatorcamera.h"

namespace black {

// TODO: REMOVE HARDCODED WIDTH / HEIGHT
SpectatorCamera::SpectatorCamera()
    : Camera(60.0f, 16.0f / 9.0f, 0.1f, 100.0f),
      m_velocity(0.05f)
{

}

SpectatorCamera::~SpectatorCamera()
{

}

void SpectatorCamera::handleKeyboard(QKeyEvent *e)
{
    switch (e->key()) {
    case Qt::Key_W:
        m_position.setY(m_position.y() + m_velocity);
        break;
    case Qt::Key_S:
        m_position.setY(m_position.y() - m_velocity);
        break;
    case Qt::Key_D:
        m_yaw -= m_velocity * 100;
        break;
    case Qt::Key_A:
        m_yaw += m_velocity * 100;
        break;
    default:
        break;
    }

    qDebug() << m_position;
    qDebug() << m_lookAt;
    qDebug() << m_upVector;

    setView(m_position, m_lookAt, m_upVector);
}

void SpectatorCamera::handleMouse(QMouseEvent *e)
{
    Q_UNUSED(e);
}

void SpectatorCamera::handleWheel(QWheelEvent *e)
{
    int degree = e->delta() / 8;

    m_position.setZ(m_position.z() - degree / 100.0f);

    setView(m_position, m_lookAt, m_upVector);
}

float SpectatorCamera::velocity() const
{
    return m_velocity;
}

void SpectatorCamera::setVelocity(float velocity)
{
    m_velocity = velocity;
}

} // end of black namespace
