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
 *
 * @version 1.1 15.03.2017
 * Texture support
 * @version 1.0 12.03.2017
 * First working version
 */
class CubeMesh : public Mesh
{
public:
    CubeMesh();
};

}
#endif // BLCUBEMESH_H
