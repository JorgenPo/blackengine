//
// Created by popof on 22.04.2018.
//

#ifndef BLACKENGINE_GLSLSHADERPROGRAM_H
#define BLACKENGINE_GLSLSHADERPROGRAM_H

#include <GLIncludes.h>
#include <memory>
#include <core/render/ShaderProgram.h>
#include "GLSLShader.h"

namespace black::render {
    /**
     * GLSL Shader program
     */
    class GLSLShaderProgram : public ShaderProgram {
        static size_t ERROR_BUFFER_LENGTH;
        GLuint program;
    public:
        GLSLShaderProgram();

        virtual ~GLSLShaderProgram();

        void link() override;

        void use() override;

    private:
        bool isLinkedSuccessfully();
        std::string getLinkError();
    };
}


#endif //BLACKENGINE_GLSLSHADERPROGRAM_H
