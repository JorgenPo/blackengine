#ifndef BLSPECTATORCAMERA_H
#define BLSPECTATORCAMERA_H

#include "src/core/blcamera.h"
#include <QPoint>

namespace black {

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
};

} // end of black namespace

#endif // BLSPECTATORCAMERA_H
