#ifndef BLAPPLICATION_H
#define BLAPPLICATION_H

/* Standard */
#include <memory>

/* Qt */
#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>

/* Core */
#include <src/core/blmesh.h>
#include <src/core/blcamera.h>
#include <src/core/blshaderprogram.h>
#include <src/core/blmodel.h>
#include <src/core/blconstants.h>
#include <src/core/bltexture.h>

/* Utils */
#include <src/utils/bllight.h>
#include <src/utils/blcubemesh.h>
#include <src/utils/bltimer.h>

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
    virtual void mouseMoveEvent(QMouseEvent *);
private:
    void initModels();
    void loadResources();
    void prepareToRender();

private:
    std::unique_ptr<black::ShaderProgram> m_program;
    std::unique_ptr<black::ShaderProgram> m_diffuseShader;

    std::shared_ptr<black::Shader> m_vShader;
    std::shared_ptr<black::Shader> m_fShader;

    std::unique_ptr<black::CubeMesh> m_cubeMesh;
    std::unique_ptr<black::Mesh> m_axisMesh;

    bool m_initialized = false;

    black::Camera* m_currentCamera;
    std::unique_ptr<black::Camera> m_specCamera;
    std::unique_ptr<black::Camera> m_objCamera;
    std::unique_ptr<black::Timer> m_timer;

    // Handled by rm
    std::shared_ptr<black::Model> m_stallMesh;
    std::shared_ptr<black::Model> m_bodyMesh;
    std::shared_ptr<black::Model> m_monkeyMesh;
    std::shared_ptr<black::Model> m_houseModel;
    std::shared_ptr<black::Model> m_landModel;
    std::shared_ptr<black::Model> m_cubeModel;
    std::shared_ptr<black::Model> m_planeModel;
    std::shared_ptr<black::Model> m_skyBoxModel;
    std::shared_ptr<black::Model> m_flyingIslandModel;

    std::shared_ptr<black::Texture> m_brickTexture;

    std::unique_ptr<black::Light> m_lightSource;

    // QWindow interface
protected:
    void wheelEvent(QWheelEvent *) override;
};

#endif // BLAPPLICATION_H
