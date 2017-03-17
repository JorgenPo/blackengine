#include "blcamera.h"

namespace black {

Camera::Camera(float fov, float ratio, float near, float far)
    : m_perspective(), m_fov(fov), m_ratio(ratio),
      m_near(near), m_far(far),
      m_view(), m_position(0.0f, 0.4f, 1.0f),
      m_lookAt(), m_upVector(0, 1, 0)
{
    Logger::getInstance() << "lookat: " << m_lookAt;
    setPerspective(fov, ratio, near, far);
    setView(m_position, m_lookAt, m_upVector);
}

Camera::~Camera()
{

}

void Camera::setPosition(const QVector3D &position)
{
    m_position = position;
    setView(m_position, m_lookAt, m_upVector);
}

void Camera::setLookAt(const QVector3D &lookAt)
{
    m_lookAt = lookAt;
    setView(m_position, m_lookAt, m_upVector);
}

void Camera::setUpVector(const QVector3D &upVector)
{
    m_upVector = upVector;
    setView(m_position, m_lookAt, m_upVector);
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

void Camera::setPerspective(float fov, float ratio, float near, float far)
{
    m_perspective.setToIdentity();
    m_perspective.perspective(fov, ratio, near, far);
}

void Camera::setPerspective(const QMatrix4x4 &perspective)
{
    m_perspective = perspective;
}

void Camera::setFov(float fov)
{
    m_fov = fov;
    setPerspective(m_fov, m_ratio, m_near, m_far);
}

void Camera::setAspectRatio(float ratio)
{
    m_ratio = ratio;
    setPerspective(m_fov, m_ratio, m_near, m_far);
}

void Camera::setNearPlane(float near)
{
    m_near = near;
    setPerspective(m_fov, m_ratio, m_near, m_far);
}

void Camera::setFarPlane(float far)
{
    m_far = far;
    setPerspective(m_fov, m_ratio, m_near, m_far);
}

void Camera::setView(const QVector3D &position, const QVector3D &lookAt, const QVector3D &up)
{
    m_position = position;
    m_lookAt = lookAt;
    m_upVector = up;

    m_view.setToIdentity();
    m_view.lookAt(m_position, m_lookAt, m_upVector);
    m_view.rotate(m_pitch, 1.0f, 0.0f, 0.0f);
    m_view.rotate(m_yaw,   0.0f, 1.0f, 0.0f);
    m_view.rotate(m_roll,  0.0f, 0.0f, 1.0f);
}

void Camera::setView(const QMatrix4x4 &view)
{
    m_view = view;
}


}
