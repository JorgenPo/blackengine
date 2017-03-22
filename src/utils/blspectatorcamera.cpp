#include "blspectatorcamera.h"

#include <cmath>
#include <bllogger.h>

#include <QCursor>

namespace black {

SpectatorCamera::SpectatorCamera()
    : Camera(), m_lastMousePos(), m_firstMouseEvent()
{
    this->setPosition({0.0, 5.0f, 20.0f});

    this->setPitchConstraint(90);
    this->setYawConstraint(90);
}

void SpectatorCamera::handleKeyboard(QKeyEvent *e)
{
    int speed = 10.0f;
    switch ( e->key() ) {
    case Qt::Key_Left:
    case Qt::Key_A:
        this->moveLeft(speed);
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        this->moveRight(speed);
        break;
    case Qt::Key_Up:
    case Qt::Key_W:
        this->moveForward(speed);
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        this->moveBack(speed);
        break;
    default:
        break;
    }
}

void SpectatorCamera::handleMouse(QMouseEvent *e)
{
    if ( !m_firstMouseEvent ) {
        float dx = QCursor::pos().x() - m_lastMousePos.x();
        float dy = m_lastMousePos.y() - QCursor::pos().y();
        dx *= 0.5f;
        dy *= 0.5f;

        this->setRotate({m_pitch + dy, m_yaw + dx, m_roll});
    } else {
        m_firstMouseEvent = false;
    }

    m_lastMousePos = QCursor::pos();
}

void SpectatorCamera::handleWheel(QWheelEvent *e)
{

}

} // end of black namespace
