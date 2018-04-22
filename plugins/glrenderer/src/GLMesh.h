//
// Created by popof on 22.04.2018.
//

#ifndef BLACKENGINE_GLMESH_H
#define BLACKENGINE_GLMESH_H

#include "GLIncludes.h"
#include <core/render/Mesh.h>

namespace black::render {

    /**
     * OpenGL specific mesh
     */
    class GLMesh : public Mesh {
        GLuint vbo;
    public:
        explicit GLMesh(std::vector<float> vertices);

        virtual ~GLMesh();

        void bind() override;

        void unbind() override;

        void update() override;
    };
}


#endif //BLACKENGINE_GLMESH_H
