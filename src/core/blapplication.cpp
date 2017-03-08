#include "blapplication.h"

#include <QDebug>
#include <QSurfaceFormat>

using std::make_unique;

BLApplication::BLApplication(QWidget *parent)
    : QOpenGLWidget(parent)
{
    QSurfaceFormat format;
    format.setMajorVersion(3);
    format.setMinorVersion(1);
    //format.setProfile(QSurfaceFormat::CoreProfile);

    this->setFormat(format);

    connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
}

BLApplication::~BLApplication()
{
    m_program.release();
    m_vShader.release();
    m_fShader.release();

    m_triangleMesh.release();
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

    if ( !m_program->link() ) {
        qDebug() << m_vShader->log();
        qDebug() << m_fShader->log();
        qDebug() << m_program->log();
        exit(3);
    }

    m_program->bind();

    initModels();

    m_initialized = true;
}

void BLApplication::resizeGL(int w, int h)
{
    int side = qMin(w, w);
    glViewport((w - side) / 2, (h - side) / 2, side, side);
}

void BLApplication::paintGL()
{
    if ( !m_initialized ) {
        return;
    }

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    QColor color("yellow");

    m_program->bind();

    m_program->setAttributeValue(PROGRAM_VERTEX_COL, color);

    m_triangleMesh->render();

    m_program->release();
}

void BLApplication::initModels()
{

    m_triangleMesh = make_unique<black::Mesh>(m_program.get());

    m_triangleMesh->setPositionData({
        0.5f,  0.5f,  0.0f,
        1.0f,  0.0f, 0.0f,
        0.0f,  0.0f, 0.0f
    });
}
