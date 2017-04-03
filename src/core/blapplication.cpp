#include "blmaterial.h"

#include <blapplication.h>
#include <blresourcemanager.h>
#include <blobjectcamera.h>
#include <bltexture.h>
#include <bllogger.h>
#include <blspectatorcamera.h>
#include <diffuseshader.h>

#include <QMouseEvent>
#include <QSurfaceFormat>

#include <QtMath>

#include <GL/gl.h>

using std::make_unique;
using std::make_shared;
using namespace black;

BLApplication::BLApplication(QWindow *parent)
    : QOpenGLWindow(NoPartialUpdate, parent),
      m_specCamera(),
      m_timer(),
      m_stallMesh(),
      m_bodyMesh(),
      m_brickTexture(),
      m_lightSource()
{
    QSurfaceFormat format;
    format.setMajorVersion(Constants::OPENGL_MAJOR_VERSION);
    format.setMinorVersion(Constants::OPENGL_MINOR_VERSION);
    format.setDepthBufferSize(24);
    format.setProfile(QSurfaceFormat::CoreProfile);

    setWidth(Constants::WIDTH);
    setHeight(Constants::HEIGHT);

    this->setFormat(format);

    m_specCamera = make_unique<SpectatorCamera>();
    m_objCamera = make_unique<SpectatorCamera>();
    m_currentCamera = m_specCamera.get();
    m_timer = make_unique<Timer>();

    this->setMouseGrabEnabled(true);

    connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
}

BLApplication::~BLApplication()
{
    m_program.release();
    m_specCamera.release();
    m_cubeMesh.release();
    m_axisMesh.release();
    m_timer.release();
    m_lightSource.release();

    /* Models */
    m_stallMesh.reset();
    m_bodyMesh.reset();
    m_monkeyMesh.reset();
    m_houseModel.reset();
    m_landModel.reset();
    m_cubeMesh.reset();
    m_planeModel.reset();
    m_skyBoxModel.reset();
    m_flyingIslandModel.reset();

    m_brickTexture.reset();


}

void BLApplication::initializeGL()
{

    initializeOpenGLFunctions();

    auto& rm = ResourceManager::getInstance();

    // Load shaders and init variables
    try {
        m_vShader = rm.get<Shader>("shaders/simple_vertex.vert");
        m_fShader = rm.get<Shader>("shaders/simple_fragment.frag");
    } catch(std::string e) { // TODO: exceptions
        Logger::getInstance() << m_vShader->log() << std::endl;
        Logger::getInstance() << m_fShader->log() << std::endl;
        exit(1);
    }

    try {
        m_program = make_unique<ShaderProgram>(m_vShader, m_fShader);
    } catch(std::string e) { // TODO: exceptions
        exit(1);
    }

    try {
        m_diffuseShader = make_unique<DiffuseShader>();
    } catch(std::string e) { // TODO: exceptions
        exit(1);
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
    m_specCamera->setAspectRatio(ratio);
}

void BLApplication::paintGL()
{
    m_timer->tick();

    static double dCoord = 0.0001;

    if ( !m_initialized ) {
        return;
    }

    prepareToRender();

    m_program->bind();
    m_program->setCamera(m_currentCamera);

    float r = 50.0f;
    m_lightSource->setPosition({sin(dCoord * 8.0f) * r, 100.0f, cos(dCoord * 8.0f) * r});

    m_program->setLight(m_lightSource.get());

    /* LAND MODEL */
    m_landModel->setPositionY(-15.0f);
    m_program->setModelMatrix(m_landModel->modelMatrix());
    m_program->setMaterial(m_landModel->material());
    m_landModel->render();

    glCullFace(GL_FRONT);
    m_flyingIslandModel->setPosition(450.0f, -20.0f, 80.0f);
    m_program->setModelMatrix(m_flyingIslandModel->modelMatrix());
    m_program->setMaterial(m_flyingIslandModel->material());
    m_flyingIslandModel->render();
    glCullFace(GL_BACK);

//    /* PLANE MODEL */
//    m_planeModel->setScale(dCoord);
//    m_program->setWorldMatrix(m_camera->perspective() * m_camera->view() * m_planeModel->modelMatrix());
//    m_planeModel->render();

    QMatrix4x4 mvpMatrix;

    m_program->disableTextures();

    /* BODY MODEL */
    m_program->setModelMatrix(m_bodyMesh->modelMatrix());
    m_program->setMaterial(m_bodyMesh->material());
    m_bodyMesh->render();

    /* Monkey mask */
    m_program->setModelMatrix(m_monkeyMesh->modelMatrix());
    m_program->setMaterial(m_monkeyMesh->material());
    m_monkeyMesh->render();

    /* HOUSE MODEL */
    m_program->setModelMatrix(m_houseModel->modelMatrix());
    m_program->setMaterial(m_houseModel->material());
    m_houseModel->render();

    /* Stall mesh */
    m_program->setModelMatrix(m_stallMesh->modelMatrix());
    m_program->setMaterial(m_stallMesh->material());
    m_stallMesh->render();

    m_program->enableTextures();

    /* AXIS MESH */
    mvpMatrix.setToIdentity();
    mvpMatrix = m_specCamera->perspective() * m_specCamera->view() * mvpMatrix;

    mvpMatrix.setToIdentity();

    m_axisMesh->bind();

    if ( m_axisMesh->isIndexed() ) {
        glDrawElements(GL_TRIANGLE_STRIP, m_axisMesh->vertexCount(), GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(GL_LINE_STRIP, 0, m_axisMesh->vertexCount());
    }

    m_axisMesh->release();
    m_program->release();

    m_diffuseShader->bind();

    /* SKY BOX */
    glDisable(GL_CULL_FACE);

    m_skyBoxModel->setScale(1000.0f);
    m_diffuseShader->setCamera(m_currentCamera);
    m_diffuseShader->setModelMatrix(m_skyBoxModel->modelMatrix());
    m_skyBoxModel->render();

    m_diffuseShader->release();

    dCoord += 0.002f;

    //Logger::getInstance() << "mpf = " << m_timer->mpf() << '\n';
    //Logger::getInstance() << "fps = " << m_timer->fps() << '\n';
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

    m_lightSource = make_unique<Light>();
}

void BLApplication::loadResources()
{
    auto& rm = ResourceManager::getInstance();

    /* TEXTURES */
    auto guid = rm.load<Texture>("textures/default.jpg");

    /* MATERIALS */
    guid = rm.load<Material>("materials/default.mtl");

    /* MODELS */
    guid = rm.load<Model>("models/cube_textured.obj");
    m_cubeModel = rm.get<Model>(guid);

    guid = rm.load<Model>("models/skybox.obj");
    m_skyBoxModel = rm.get<Model>(guid);

    guid = rm.load<Model>("models/plane.obj");
    m_planeModel = rm.get<Model>(guid);

    guid = rm.load<Model>("models/stall.obj");
    m_stallMesh = rm.get<Model>(guid);

    guid = rm.load<Model>("models/body_triangulated.obj");
    m_bodyMesh = rm.get<Model>(guid);

    guid = rm.load<Model>("models/monkey.obj");
    m_monkeyMesh = rm.get<Model>(guid);

    guid = rm.load<Model>("models/house_triangulated.obj");
    m_houseModel = rm.get<Model>(guid);

    guid = rm.load<Model>("models/land.obj");
    m_landModel = rm.get<Model>(guid);

    guid = rm.load<Model>("models/flying_island.obj");
    m_flyingIslandModel = rm.get<Model>(guid);
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
    m_currentCamera->handleWheel(event);
}

void BLApplication::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
    case Qt::Key_F1:
        m_currentCamera = m_specCamera.get();
        break;
    case Qt::Key_F2:
        m_currentCamera = m_objCamera.get();
        break;
    default:
        break;
    }

    m_currentCamera->handleKeyboard(event);
}

void BLApplication::mouseMoveEvent(QMouseEvent *event)
{
    m_currentCamera->handleMouse(event);
}
