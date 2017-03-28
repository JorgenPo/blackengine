#ifndef BLSPECTATORCAMERA_H
#define BLSPECTATORCAMERA_H

#include "src/core/blcamera.h"
#include <QPoint>

namespace black {

/**
 * @brief The SpectatorCamera class
 *  Freely movable fps camera.
 *
 * @version 1.1 28.03.2017
 * Slightly remake camera behavior.
 * Almost all is working well.
 *
 * @version 1.0 22.03.2017
 * Working version. Some bugs.
 *
 * @author george popoff <popoff96@live.com>
 *
 */
class SpectatorCamera : public Camera
{
public:
    SpectatorCamera();

    // Camera interface
public:
    void handleKeyboard(QKeyEvent *e) override;
    void handleMouse(QMouseEvent *e) override;
    void handleWheel(QWheelEvent *e) override;

private:
    QPointF m_lastMousePos;
    bool m_firstMouseEvent;

    float m_speed;
    float m_smoothness;
};

} // end of black namespace

#endif // BLSPECTATORCAMERA_H
