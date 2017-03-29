#ifndef BLCAMERA_H
#define BLCAMERA_H

#include <QMatrix4x4>
#include <QMouseEvent>

#include <algorithm>

namespace black {

/**
 * @brief The Camera class is
 *  base class for all camera
 *  types in engine.
 *
 * @version 1.1 28.03.2017
 * Changed algorythm of rotations (pitch, yaw, roll).
 * Now are using trigonometry rules. Working well.
 *
 * @version 1.0 22.03.2017
 * Working camera.
 *
 * @author george popoff <popoff96@live.com>
 *
 */
class Camera {

public:

    Camera();
    Camera(const Camera &camera);
    Camera(float fov, float ratio, float nearPlane, float farPlane);

    virtual ~Camera();

    // Setters
    void setPerspective(float fov, float ratio,
                        float nearPlane, float farPlane);

    void setPerspective(const QMatrix4x4 &perspective);

    void setFov(float fov);
    void setAspectRatio(float ratio);
    void setNearPlane(float nearPlane);
    void setFarPlane(float farPlane);

    void setView(const QVector3D &position,
                 const QVector3D &lookAt,
                 const QVector3D &up);

    void setView(const QMatrix4x4 &view);

    void setPosition(const QVector3D &position);
    void setLookAt(const QVector3D &lookAt);
    void setUpVector(const QVector3D &upVector);

    void move(const QVector3D &moveVector);
    void moveRight(float dist);
    void moveLeft(float dist);
    void moveDown(float dist);
    void moveUp(float dist);
    void moveForward(float dist);
    void moveBack(float dist);

    void setRotate(const QVector3D& rotation);
    void setPitch(float pitch);
    void setYaw(float yaw);
    void setRoll(float roll);

    void setPitchConstraint(float max);
    void setYawConstraint(float max);
    void setRollConstraint(float max);

    // Getters
    float fov() const { return m_fov; }
    float ratio() const { return m_ratio; }
    float nearPlane() const { return m_near; }
    float farPlane() const { return m_far; }

    const QMatrix4x4& perspective();
    const QMatrix4x4& view();
    const QMatrix4x4& perspective() const;
    const QMatrix4x4& view() const;

    QVector3D position() const { return m_position; }
    QVector3D lookAt() const { return m_lookAt; }
    QVector3D upVector() const { return m_upVector; }

    virtual void handleKeyboard(QKeyEvent *e);
    virtual void handleMouse(QMouseEvent *e);
    virtual void handleWheel(QWheelEvent *e);

private:
    void updateLookAt();

protected:
    QMatrix4x4 m_perspective;

    float m_fov;
    float m_ratio;
    float m_near;
    float m_far;

    QMatrix4x4 m_view;

    QVector3D  m_position;
    QVector3D  m_lookAt;
    QVector3D  m_upVector;

    float m_pitch; // x rotation
    float m_yaw;   // y rotation
    float m_roll;  // z rotation

    float m_pitchConstraint;
    float m_yawConstraint;
    float m_rollConstraint;

    bool m_needUpdateView;
    bool m_needUpdatePerspective;
};

} // end of black namespace

#endif // BLCAMERA_H
