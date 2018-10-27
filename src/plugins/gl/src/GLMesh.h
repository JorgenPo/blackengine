//
// Created by popof on 09.10.2018.
//

#ifndef BLACKENGINE_GLMESH_H
#define BLACKENGINE_GLMESH_H

#include <CommonHeaders.h>
#include <Mesh.h>

#include "OpenGLCommonHeaders.h"

namespace black {
    /**
     * OpenGL Mesh
     */
    class GLMesh : public Mesh {
        GLuint positionVbo;
        GLuint vao;

    public:
        explicit GLMesh(const std::vector<float> &vertices);

        void bind() override;

        int getDrawMode() const override;

    private:
        void createMesh();
    };
}


#endif //BLACKENGINE_GLMESH_H