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
#include <blmesh.h>
#include <blcamera.h>
#include <blshaderprogram.h>
#include <blmodel.h>
#include <blconstants.h>
#include <bltexture.h>
#include <blterrain.h>

/* Utils */
#include <bllight.h>
#include <blcubemesh.h>
#include <bltimer.h>

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
    void loadResources();
    void prepareToRender();

private:
    std::unique_ptr<black::ShaderProgram> m_program;
    std::unique_ptr<black::ShaderProgram> m_diffuseShader;

    std::shared_ptr<black::Shader> m_vShader;
    std::shared_ptr<black::Shader> m_fShader;

    bool m_initialized = false;

    std::shared_ptr<black::Camera> m_currentCamera;
    std::shared_ptr<black::Camera> m_specCamera;
    std::shared_ptr<black::Camera> m_objCamera;
    std::unique_ptr<black::Timer> m_timer;

    // Handled by rm
    std::shared_ptr<black::Terrain> m_terrain;
    std::shared_ptr<black::Model> m_stallMesh;
    std::shared_ptr<black::Model> m_bodyMesh;
    std::shared_ptr<black::Model> m_monkeyMesh;
    std::shared_ptr<black::Model> m_houseModel;
    std::shared_ptr<black::Model> m_landModel;
    std::shared_ptr<black::Model> m_skyBoxModel;
    std::shared_ptr<black::Model> m_flyingIslandModel;

    std::shared_ptr<black::Texture> m_brickTexture;

    std::shared_ptr<black::Light> m_lightSource;

    // QWindow interface
protected:
    void wheelEvent(QWheelEvent *) override;
};

#endif // BLAPPLICATION_H
