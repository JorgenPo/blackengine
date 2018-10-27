#ifndef BLACKENGINE_GLSLSHADER_H
#define BLACKENGINE_GLSLSHADER_H

#include "OpenGLCommonHeaders.h"
#include <shader/Shader.h>

namespace black {
    class GLSLShader : public Shader {
        static size_t ERROR_BUFFER_LENGTH;
        GLuint shader;

    public:
        /**
         * Very simple vertex shader code
         */
        static constexpr auto SimpleVertex =
                "#version 330 core\n"
                "layout (location = 0) in vec3 pos;\n"
                "\n"
                "uniform mat4 projection;\n"
                "uniform mat4 view;\n"
                "uniform mat4 model;\n"
                ""
                "\n"
                "void main()\n"
                "{\n"
                "    gl_Position = projection * view * model * vec4(pos, 1.0);\n"
                "}";

        /**
         * Very simple fragment shader code
         */
        static constexpr auto SimpleFragment =
                "#version 330 core\n"
                "out vec4 FragColor;\n"
                "\n"
                "void main()\n"
                "{\n"
                "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                "} ";

    public:
        GLSLShader(const std::string &code, Type type);

        virtual ~GLSLShader();

        void compile() override;

        void *getImplementation() override;

    private:
        GLenum toGLShaderType(Type type);
        bool isCompiledSuccessfully();
        std::string getCompilationError();
    };
}


#endif //BLACKENGINE_GLSLSHADER_H
