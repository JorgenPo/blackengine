#include <blobjectcamera.h>
#include <blconstants.h>

namespace black {

ObjectCamera::ObjectCamera()
    : Camera(),
      m_velocity(0.05f)
{

}

ObjectCamera::~ObjectCamera()
{

}

void ObjectCamera::handleKeyboard(QKeyEvent *e)
{
    switch (e->key()) {
    case Qt::Key_W:
        this->moveForward(m_velocity);
        break;
    case Qt::Key_S:
        this->moveBack(m_velocity);
        break;
    case Qt::Key_D:
        this->setYaw(m_yaw - m_velocity * 100);
        break;
    case Qt::Key_A:
        this->setYaw(m_yaw + m_velocity * 100);
        break;
    default:
        break;
    }

    qDebug() << m_position;
    qDebug() << m_lookAt;
    qDebug() << m_upVector;

    setView(m_position, m_lookAt, m_upVector);
}

void ObjectCamera::handleMouse(QMouseEvent *e)
{
    Q_UNUSED(e);
}

void ObjectCamera::handleWheel(QWheelEvent *e)
{
    int degree = e->delta() / 8;

    m_position.setZ(m_position.z() - degree / 100.0f);

    setView(m_position, m_lookAt, m_upVector);
}

float ObjectCamera::velocity() const
{
    return m_velocity;
}

void ObjectCamera::setVelocity(float velocity)
{
    m_velocity = velocity;
}

} // end of black namespace
