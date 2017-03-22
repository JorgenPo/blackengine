#ifndef BL_OBJECTCAMERA_H
#define BL_OBJECTCAMERA_H

#include "src/core/blcamera.h"

namespace black {

/**
 * @brief The SpectatorCamera class represents
 *  freely movable camera
 */
class ObjectCamera : public Camera {

public:

    ObjectCamera();

    ~ObjectCamera();

    // Camera interface
    float velocity() const;
    void setVelocity(float velocity);

private:
    void handleKeyboard(QKeyEvent *e) override;
    void handleMouse(QMouseEvent *e) override;
    void handleWheel(QWheelEvent *e) override;

private:
    float m_velocity;
};

} // end of black namespace

#endif // BLSPECTATORCAMERA_H
