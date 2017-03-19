#ifndef BLAPPLICATION_H
#define BLAPPLICATION_H

#include <memory>

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <bllight.h>


#include "src/core/blmesh.h"
#include "src/core/blcamera.h"

#include "src/utils/blcubemesh.h"
#include "src/utils/bltimer.h"

#include "bltexture.h"
#include "blconstants.h"
#include "blmodel.h"

using std::unique_ptr;
using std::shared_ptr;

class BLApplication : public QOpenGLWindow, public QOpenGLFunctions {

public:
    BLApplication(QWindow *parent = nullptr);

    virtual ~BLApplication();


protected:
    // QOpenGLWidget interface
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

    // QWidget interface
    virtual void keyPressEvent(QKeyEvent *event);

private:
    void initModels();
    void loadResources();
    void prepareToRender();

private:
    unique_ptr<QOpenGLShaderProgram> m_program;
    unique_ptr<QOpenGLShader> m_vShader;
    unique_ptr<QOpenGLShader> m_fShader;

    unique_ptr<black::CubeMesh> m_cubeMesh;
    unique_ptr<black::Mesh> m_axisMesh;

    bool m_initialized = false;

    unique_ptr<black::Camera> m_camera;

    unique_ptr<black::Timer> m_timer;

    // Handled by rm
    std::shared_ptr<black::Model> m_stallMesh;
    std::shared_ptr<black::Model> m_bodyMesh;
    std::shared_ptr<black::Model> m_monkeyMesh;

    std::shared_ptr<black::Texture> m_brickTexture;

    unique_ptr<black::Light> m_lightSource;

    // QWindow interface
protected:
    void wheelEvent(QWheelEvent *) override;
};

#endif // BLAPPLICATION_H
