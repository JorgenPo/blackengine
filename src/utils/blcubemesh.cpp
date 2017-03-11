#include "blcubemesh.h"

namespace black {

CubeMesh::CubeMesh(QOpenGLShaderProgram *program)
    : Mesh(program)
{
    this->setPositionData({
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f
    });

    this->setIndexData({
        0, 2, 3, 0, 1, 2, // Front
        1, 5, 2, 1, 7, 5, // Right
        7, 0, 6, 7, 1, 0, // Bottom
        7, 4, 5, 7, 6, 4, // Far
        6, 3, 4, 6, 0, 3, // Left
        3, 5, 4, 3, 2, 5, // Top
                             });
}

} // end of black namespace
