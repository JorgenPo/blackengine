//
// Created by popof on 22.04.2018.
//

#ifndef BLACKENGINE_GLSLSHADER_H
#define BLACKENGINE_GLSLSHADER_H

#include "GLIncludes.h"
#include <core/render/Shader.h>

namespace black::render {
    class GLSLShader : public Shader {
        static size_t ERROR_BUFFER_LENGTH;

        GLuint shader;

    public:
        GLSLShader(const std::string &code, Type type);

        virtual ~GLSLShader();

        void compile() override;

    private:
        GLenum toGLShaderType(Type type);
        bool isCompiledSuccessfully();
        std::string getCompilationError();
    };
}


#endif //BLACKENGINE_GLSLSHADER_H
