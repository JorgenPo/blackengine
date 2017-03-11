#ifndef BLCUBEMESH_H
#define BLCUBEMESH_H

#include <QOpenGLShaderProgram>

#include "src/core/blmesh.h"

namespace black {

/**
 * @brief The CubeMesh class
 * Provides simple cube with a side equals one
 * mesh without colour.
 *
 * @author george popoff <popoff96@live.com>
 * @date 12.03.2017
 * @version 1.0 First working version
 */
class CubeMesh : public Mesh
{
public:
    CubeMesh(QOpenGLShaderProgram *program);
};

}
#endif // BLCUBEMESH_H
