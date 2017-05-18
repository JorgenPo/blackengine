#include "blmaterial.h"

#include <blapplication.h>
#include <blresourcemanager.h>
#include <blobjectcamera.h>
#include <bltexture.h>
#include <bllogger.h>
#include <blspectatorcamera.h>
#include <blrenderer.h>

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

    m_specCamera = make_shared<SpectatorCamera>();
    m_objCamera = make_shared<SpectatorCamera>();
    m_currentCamera = m_specCamera;
    m_timer = make_unique<Timer>();

    this->setMouseGrabEnabled(true);

    connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
}

BLApplication::~BLApplication()
{
    m_program.reset();
    m_specCamera.reset();
    m_timer.reset();
    m_lightSource.reset();

    /* Models */
    m_stallMesh.reset();
    m_bodyMesh.reset();
    m_monkeyMesh.reset();
    m_houseModel.reset();
    m_landModel.reset();
    m_skyBoxModel.reset();
    m_flyingIslandModel.reset();
    m_terrain.reset();

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

    Renderer::getInstance().setProgram(m_program);

    try {
        m_diffuseShader = make_unique<DiffuseShader>();
    } catch(std::string e) { // TODO: exceptions
        exit(1);
    }

    loadResources();

    m_lightSource = make_shared<Light>();

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

    float r = 50.0f;
    m_lightSource->setPosition({sin(dCoord * 8.0f) * r, 100.0f, cos(dCoord * 8.0f) * r});

    auto& renderer = Renderer::getInstance();

    renderer.setProgram(m_program);
    renderer.setCamera(m_currentCamera);
    renderer.setLight(m_lightSource);

    /* LAND MODEL */
    //renderer.renderTerrain(m_terrain);

    m_landModel->setPositionY(-15.0f);
    renderer.renderModel(m_landModel);

    glCullFace(GL_FRONT);

    m_flyingIslandModel->setPosition(450.0f, -20.0f, 80.0f);
    renderer.renderModel(m_flyingIslandModel);

    glCullFace(GL_BACK);

    m_program->disableTextures();

    /* BODY MODEL */
    renderer.renderModel(m_bodyMesh);

    /* Monkey mask */
    renderer.renderModel(m_monkeyMesh);

    /* HOUSE MODEL */
    renderer.renderModel(m_houseModel);

    /* Stall mesh */
    renderer.renderModel(m_stallMesh);

    m_program->enableTextures();

    QMatrix4x4 mvpMatrix;

    renderer.setProgram(m_diffuseShader);

    /* SKY BOX */
    glDisable(GL_CULL_FACE);

    m_skyBoxModel->setScale(1000.0f);
    renderer.renderModel(m_skyBoxModel);

    dCoord += 0.002f;

    //Logger::getInstance() << "mpf = " << m_timer->mpf() << '\n';
    //Logger::getInstance() << "fps = " << m_timer->fps() << '\n';
}

void BLApplication::loadResources()
{
    auto& rm = ResourceManager::getInstance();

    /* TEXTURES */
    auto guid = rm.load<Texture>("textures/default.jpg");

    /* MATERIALS */
    guid = rm.load<Material>("materials/default.mtl");

    /* MODELS */
    m_terrain = std::make_shared<Terrain>(800, 600, 80, 60, rm.get<Texture>("textures/grass.jpg"));


    guid = rm.load<Model>("models/skybox.obj");
    m_skyBoxModel = rm.get<Model>(guid);
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
        m_currentCamera = m_specCamera;
        break;
    case Qt::Key_F2:
        m_currentCamera = m_objCamera;
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
