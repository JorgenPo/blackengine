#include "blapplication.h"
#include "blresourcemanager.h"
#include "blspectatorcamera.h"
#include "bltexture.h"

#include <QDebug>
#include <QMouseEvent>
#include <QSurfaceFormat>

#include <GL/gl.h>

using std::make_unique;
using std::make_shared;
using namespace black;

BLApplication::BLApplication(QWindow *parent)
    : QOpenGLWindow(NoPartialUpdate, parent),
      m_camera(),
      m_timer(),
      m_brickTexture(),
      m_stallMesh(),
      m_bodyMesh()
{
    QSurfaceFormat format;
    format.setMajorVersion(3);
    format.setMinorVersion(3);
    format.setDepthBufferSize(24);
    format.setProfile(QSurfaceFormat::CoreProfile);

    setWidth(800);
    setHeight(600);

    this->setFormat(format);

    m_camera = make_unique<SpectatorCamera>();
    m_timer = make_unique<Timer>();

    connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
}

BLApplication::~BLApplication()
{
    m_program.release();
    m_vShader.release();
    m_fShader.release();
    m_camera.release();
    m_cubeMesh.release();
    m_timer.release();
}

void BLApplication::initializeGL()
{

    initializeOpenGLFunctions();

    m_vShader = make_unique<QOpenGLShader>(
                QOpenGLShader::Vertex);
    m_fShader = make_unique<QOpenGLShader>(
                QOpenGLShader::Fragment);

    m_vShader->compileSourceFile("shaders/simple_vertex.vert");
    m_fShader->compileSourceFile("shaders/simple_fragment.frag");

    if ( !m_vShader->isCompiled() ) {
        qDebug() << m_vShader->log();
        exit(1);
    }
    if ( !m_fShader->isCompiled() ) {
        qDebug() << m_fShader->log();
        exit(2);
    }

    m_program = make_unique<QOpenGLShaderProgram>(this);
    m_program->addShader(m_vShader.get());
    m_program->addShader(m_fShader.get());

    m_program->bindAttributeLocation("vPosition", PROGRAM_VERTEX_POS);
    m_program->bindAttributeLocation("vColor", PROGRAM_VERTEX_COL);
    m_program->bindAttributeLocation("vTexCoords", PROGRAM_VERTEX_TEX);

    if ( !m_program->link() ) {
        qDebug() << m_vShader->log();
        qDebug() << m_fShader->log();
        qDebug() << m_program->log();
        exit(3);
    }

    m_program->bind();

    loadResources();
    initModels();

    m_initialized = true;

    m_timer->run();
}

void BLApplication::resizeGL(int w, int h)
{
    int side = qMin(w, h);
    glViewport((w - side) / 2, (h - side) / 2, side, side);

    float ratio = w / (float) h;
    m_camera->setAspectRatio(ratio);
}

void BLApplication::paintGL()
{
    m_timer->tick();

    static float dCoord = 0.0001f;

    if ( !m_initialized ) {
        return;
    }

    prepareToRender();

    QMatrix4x4 mvpMatrix;
    mvpMatrix.setToIdentity();
    mvpMatrix.scale(0.2f);
    mvpMatrix.rotate(dCoord * 100.0f, 0.0f, 1.0f, 0.0f);

    mvpMatrix = m_camera->perspective() * m_camera->view() * mvpMatrix;

    m_program->bind();
    m_program->setUniformValue("mMatrix", mvpMatrix);

    m_stallMesh->bind();
    m_brickTexture->bind();

    if ( m_stallMesh->isIndexed() ) {
        glDrawElements(GL_TRIANGLE_STRIP, m_stallMesh->vertexCount(), GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(GL_TRIANGLES, 0, m_stallMesh->vertexCount());
    }

    m_stallMesh->release();
    m_brickTexture->release();

    mvpMatrix.setToIdentity();
    mvpMatrix = m_camera->perspective() * m_camera->view() * mvpMatrix;

    m_program->setUniformValue("mMatrix", mvpMatrix);

    m_axisMesh->bind();

    if ( m_axisMesh->isIndexed() ) {
        glDrawElements(GL_TRIANGLE_STRIP, m_axisMesh->vertexCount(), GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(GL_LINE_STRIP, 0, m_axisMesh->vertexCount());
    }

    m_axisMesh->release();
    m_program->release();

    dCoord += 0.002f;

    qDebug() << "mpf = " << m_timer->mpf();
    qDebug() << "fps = " << m_timer->fps();
}

void BLApplication::initModels()
{

    m_cubeMesh = make_unique<CubeMesh>();

    //Renders axis to the screen
    m_axisMesh = make_unique<Mesh>();

    m_axisMesh->setPositionData({
       0.0f, 0.0f, 0.0f,
       0.0f, 1.0f, 0.0f,
       0.0f, 0.0f, 0.0f,
       1.0f, 0.0f, 0.0f,
       0.0f, 0.0f, 0.0f,
       0.0f, 0.0f, 1.0f,
    });
}

void BLApplication::loadResources()
{
    // TODO: maybe Separate loading and init models

    auto& rm = ResourceManager::getInstance();

    auto guid = rm.load<Texture>("textures/bricks_xxl.jpg");
    m_brickTexture = rm.get<Texture>(guid);

    guid = rm.load<Mesh>("models/stall.obj");
    m_stallMesh = rm.get<Mesh>(guid);

    guid = rm.load<Mesh>("models/body.obj");
    m_bodyMesh = rm.get<Mesh>(guid);
}

void BLApplication::prepareToRender()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);

    glClearColor(1.0f, 0.8f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void BLApplication::wheelEvent(QWheelEvent *event)
{
    m_camera->handleWheel(event);
}

void BLApplication::keyPressEvent(QKeyEvent *event)
{
    m_camera->handleKeyboard(event);
}
