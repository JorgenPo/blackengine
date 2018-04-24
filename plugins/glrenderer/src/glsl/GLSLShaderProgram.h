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

        std::map<std::string, int> uniformLocations;
    public:
        GLSLShaderProgram();

        virtual ~GLSLShaderProgram();

        void link() override;
        void use() override;

        void addUniformVariable(const std::string &name) override;

        void setUniformVariable(const std::string &name, int value) override;

        void setUniformVariable(const std::string &name, float value) override;

        void setUniformVariable(const std::string &name, bool value) override;

        void setUniformVariable(const std::string &name, double value) override;

        void setUniformVariable(const std::string &name, std::array<float, 4> value) override;

        void setUniformVariable(const std::string &name, std::array<float, 3> value) override;

        void setUniformVariable(const std::string &name, std::array<float, 2> value) override;

    private:
        bool isLinkedSuccessfully();
        std::string getLinkError();
    };
}


#endif //BLACKENGINE_GLSLSHADERPROGRAM_H
