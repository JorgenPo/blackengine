#include <blcamera.h>
#include <bllogger.h>
#include <blconstants.h>

#include <QtMath>

namespace black {

Camera::Camera()
    : m_perspective(), m_fov(45.0f), m_ratio(Constants::ASPECT_RATIO),
      m_near(0.1f), m_far(1000.0f), m_view(), m_position(0, 0, 3.0f),
      m_lookAt(0, 0, -1.0f), m_upVector(0, 1.0f, 0),
      m_needUpdateView(), m_needUpdatePerspective()
{
    setPerspective(m_fov, m_ratio, m_near, m_far);
    setView(m_position, m_lookAt, m_upVector);
}

Camera::Camera(float fov, float ratio, float near, float far)
    : Camera()
{
    m_fov = fov;
    m_ratio = ratio;
    m_near = near;
    m_far = far;

    setPerspective(fov, ratio, near, far);
}

Camera::~Camera()
{

}

void Camera::setPosition(const QVector3D &position)
{
    m_position = position;
    m_needUpdateView = true;
}

void Camera::setLookAt(const QVector3D &lookAt)
{
    m_lookAt = lookAt;
    m_needUpdateView = true;
}

void Camera::setUpVector(const QVector3D &upVector)
{
    m_upVector = upVector;
    m_needUpdateView = true;
}

void Camera::move(const QVector3D &moveVector)
{
    m_position += moveVector;
    m_needUpdateView = true;
}

void Camera::moveRight(float dist)
{
    m_position += QVector3D::normal(m_lookAt, m_upVector);
    m_needUpdateView = true;
}

void Camera::moveLeft(float dist)
{
    m_position -= QVector3D::normal(m_lookAt, m_upVector);
    m_needUpdateView = true;
}

void Camera::moveDown(float dist)
{
    //m_position.setY(m_position.y() - dist);
    //m_needUpdateView = true;
}

void Camera::moveUp(float dist)
{
    //m_position.setY(m_position.y() + dist);
    //m_needUpdateView = true;
}

void Camera::moveForward(float dist)
{
    m_position += dist * m_lookAt;
    m_needUpdateView = true;
}

void Camera::moveBack(float dist)
{
    m_position -= dist * m_lookAt;
    m_needUpdateView = true;
}

void Camera::setRotate(const QVector3D &rotation)
{
    m_pitch = qMin(rotation.x(), m_pitchConstraint);
    m_yaw   = qMin(rotation.y(), m_yawConstraint);
    m_roll  = qMin(rotation.z(), m_rollConstraint);
    updateLookAt();
}

void Camera::handleKeyboard(QKeyEvent *e)
{
    // DULL CAMERA
    Q_UNUSED(e);
}

void Camera::handleMouse(QMouseEvent *e)
{
    // DULL CAMERA
    Q_UNUSED(e);
}

void Camera::handleWheel(QWheelEvent *e)
{
    // DULL CAMERA
    Q_UNUSED(e);
}

void Camera::updateLookAt()
{
    float z = qCos(qDegreesToRadians(m_pitch)) * qCos(qDegreesToRadians(m_yaw));
    float y = -qSin(qDegreesToRadians(m_pitch));
    float x = -qCos(qDegreesToRadians(m_pitch)) * qSin(qDegreesToRadians(m_yaw));

    m_lookAt = { x, y, z };
    m_lookAt.normalize();

    m_needUpdateView = true;
}

void Camera::setPitch(float pitch)
{
    m_pitch = qMin(pitch, m_pitchConstraint);
    updateLookAt();
}

void Camera::setYaw(float yaw)
{
    m_yaw = qMin(yaw, m_yawConstraint);
    updateLookAt();
}

void Camera::setRoll(float roll)
{
    m_roll = qMin(roll, m_rollConstraint);
    updateLookAt();
}

void Camera::setPitchConstraint(float max)
{
    m_pitchConstraint = max;
}

void Camera::setYawConstraint(float max)
{
    m_yawConstraint = max;
}

void Camera::setRollConstraint(float max)
{
    m_rollConstraint = max;
}

QMatrix4x4 Camera::perspective()
{
    if ( m_needUpdatePerspective ) {
        this->setPerspective(m_fov, m_ratio, m_near, m_far);
        m_needUpdatePerspective = false;
    }

    return m_perspective;
}

QMatrix4x4 Camera::view()
{
    if ( m_needUpdateView ) {
        this->setView(m_position, m_lookAt, m_upVector);
        m_needUpdateView = false;
    }

    return m_view;
}

void Camera::setPerspective(float fov, float ratio, float near, float far)
{
    m_perspective.setToIdentity();
    m_perspective.perspective(fov, ratio, near, far);
    m_needUpdatePerspective = false;
}

void Camera::setPerspective(const QMatrix4x4 &perspective)
{
    m_perspective = perspective;
}

void Camera::setFov(float fov)
{
    m_fov = fov;
    m_needUpdatePerspective = true;
}

void Camera::setAspectRatio(float ratio)
{
    m_ratio = ratio;
    m_needUpdatePerspective = true;
}

void Camera::setNearPlane(float near)
{
    m_near = near;
    m_needUpdatePerspective = true;
}

void Camera::setFarPlane(float far)
{
    m_far = far;
    m_needUpdatePerspective = true;
}

void Camera::setView(const QVector3D &position, const QVector3D &lookAt, const QVector3D &up)
{
    m_position = position;
    m_lookAt = lookAt;
    m_upVector = up;

    m_view.setToIdentity();
    m_view.lookAt(m_position, m_position + m_lookAt, m_upVector);

    m_needUpdateView = false;
}

void Camera::setView(const QMatrix4x4 &view)
{
    m_view = view;
}


}
