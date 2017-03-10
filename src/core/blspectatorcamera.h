#ifndef BLSPECTATORCAMERA_H
#define BLSPECTATORCAMERA_H

#include "blcamera.h"

namespace black {

/**
 * @brief The SpectatorCamera class represents
 *  freely movable camera
 */
class SpectatorCamera : public Camera {

public:

    SpectatorCamera();

    ~SpectatorCamera();

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
