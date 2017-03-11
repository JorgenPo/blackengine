#ifndef BLAPPLICATION_H
#define BLAPPLICATION_H

#include <memory>

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>


#include "src/core/blmesh.h"
#include "src/core/blcamera.h"

#include "src/utils/blcubemesh.h"
#include "src/utils/bltimer.h"

using std::unique_ptr;

class BLApplication : public QOpenGLWindow, public QOpenGLFunctions {

    static const int PROGRAM_VERTEX_POS = 0;
    static const int PROGRAM_VERTEX_COL = 1;

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

private:
    unique_ptr<QOpenGLShaderProgram> m_program;
    unique_ptr<QOpenGLShader> m_vShader;
    unique_ptr<QOpenGLShader> m_fShader;

    unique_ptr<black::CubeMesh> m_cubeMesh;
    unique_ptr<black::Mesh> m_axisMesh;

    QOpenGLVertexArrayObject  m_vao;

    bool m_initialized = false;

    unique_ptr<black::Camera> m_camera;

    unique_ptr<black::Timer> m_timer;
    // QWindow interface
protected:
    void wheelEvent(QWheelEvent *) override;
};

#endif // BLAPPLICATION_H
