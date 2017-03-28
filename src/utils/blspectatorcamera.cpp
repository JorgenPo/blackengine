#include "blspectatorcamera.h"

#include <cmath>
#include <bllogger.h>

#include <QCursor>

namespace black {

SpectatorCamera::SpectatorCamera()
    : Camera(), m_lastMousePos(), m_firstMouseEvent(true),
      m_speed(1.0f), m_smoothness(0.5f)
{
    this->setPosition({0.0, 5.0f, 20.0f});

    this->setPitchConstraint(90);
    this->setYawConstraint(90);
}

void SpectatorCamera::handleKeyboard(QKeyEvent *e)
{
    switch ( e->key() ) {
    case Qt::Key_Left:
    case Qt::Key_A:
        this->moveLeft(m_speed);
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        this->moveRight(m_speed);
        break;
    case Qt::Key_Up:
    case Qt::Key_W:
        this->moveForward(m_speed);
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        this->moveBack(m_speed);
        break;
    default:
        break;
    }
}

void SpectatorCamera::handleMouse(QMouseEvent *e)
{
    float dMax = 100.0f;
    if ( !m_firstMouseEvent ) {
        float dx = e->localPos().x() - m_lastMousePos.x();
        float dy = m_lastMousePos.y() - e->localPos().y();

        if ( std::abs(dx) > dMax || std::abs(dy) > dMax ) {
            m_lastMousePos = e->localPos();
            return;
        }

        dx *= 1.0f - m_smoothness;
        dy *= 1.0f - m_smoothness;

        this->setRotate({m_pitch + dy, m_yaw + dx, m_roll});
    } else {
        m_firstMouseEvent = false;
    }

    m_lastMousePos = e->localPos();
}

void SpectatorCamera::handleWheel(QWheelEvent *e)
{

}

} // end of black namespace
