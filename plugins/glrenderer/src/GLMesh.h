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
        static const GLuint POSITION_LAYOUT;

        GLuint vbo;
        GLuint ebo;
        GLuint vao;
    public:
        explicit GLMesh(std::vector<float> vertices, std::vector<unsigned int> indices);

        virtual ~GLMesh();

        void bind() override;

        void unbind() override;

        void update() override;
    };
}


#endif //BLACKENGINE_GLMESH_H
