#ifndef BLAPPLICATION_H
#define BLAPPLICATION_H

#include <memory>

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>

#include "src/mesh.h"

using std::unique_ptr;

class BLApplication : public QOpenGLWidget, public QOpenGLFunctions {

    static const int PROGRAM_VERTEX_POS = 0;
    static const int PROGRAM_VERTEX_COL = 1;

public:
    BLApplication(QWidget *parent = nullptr);

    virtual ~BLApplication();

    // QOpenGLWidget interface
protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

private:
    void initModels();

private:
    unique_ptr<QOpenGLShaderProgram> m_program;
    unique_ptr<QOpenGLShader> m_vShader;
    unique_ptr<QOpenGLShader> m_fShader;

    unique_ptr<black::Mesh> m_triangleMesh;

    QOpenGLVertexArrayObject  m_vao;

    bool m_initialized = false;
};

#endif // BLAPPLICATION_H
