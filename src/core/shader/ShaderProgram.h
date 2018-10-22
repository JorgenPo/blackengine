#ifndef BLACKENGINE_SHADERPROGRAM_H
#define BLACKENGINE_SHADERPROGRAM_H

#include <CommonHeaders.h>

#include "Shader.h"

namespace black {

    class BLACK_EXPORTED ShaderProgramLinkException : public Exception {
    public:
        explicit ShaderProgramLinkException(const std::string &message);
    };

    class BLACK_EXPORTED ShaderProgramInvalidShaderTypeException : public Exception {
    public:
        explicit ShaderProgramInvalidShaderTypeException(const std::string &message);
    };

    class BLACK_EXPORTED ShaderProgramNotLinkedException : public Exception {
    public:
        ShaderProgramNotLinkedException();
    };

    /**
     * Shader program
     */
    class BLACK_EXPORTED ShaderProgram {
    protected:
        std::shared_ptr<Shader> vertexShader;
        std::shared_ptr<Shader> fragmentShader;

        bool linked;

    public:
        ShaderProgram();
        ShaderProgram(const std::shared_ptr<Shader> &vertexShader, const std::shared_ptr<Shader> &fragmentShader);

        /**
         * Links the program with attached shaders
         *
         * @throws ShaderProgramLinkException
         */
        virtual void link() = 0;

        /**
         * Set program as current for rendering
         */
        virtual void use() = 0;

        /**
         * Add uniform variable to the shader
         *
         * @param name Name of the uniform variable
         */
        virtual void setUniformVariable(const std::string &name, int value) = 0;
        virtual void setUniformVariable(const std::string &name, float value) = 0;
        virtual void setUniformVariable(const std::string &name, bool value) = 0;
        virtual void setUniformVariable(const std::string &name, double value) = 0;
        virtual void setUniformVariable(const std::string &name, std::array<float, 4> value) = 0;
        virtual void setUniformVariable(const std::string &name, std::array<float, 3> value) = 0;
        virtual void setUniformVariable(const std::string &name, std::array<float, 2> value) = 0;
        //virtual void setUniformVariable(const std::string &name, glm::mat4 matrix) = 0;
        //virtual void setUniformVariable(const std::string &name, glm::vec3 vector) = 0;

        const std::shared_ptr<Shader> &getVertexShader() const;
        const std::shared_ptr<Shader> &getFragmentShader() const;

        void setVertexShader(const std::shared_ptr<Shader> &vertexShader);
        void setFragmentShader(const std::shared_ptr<Shader> &fragmentShader);
        //void setGeometryShader(const std::shared_ptr<Shader> &geometryShader);

        bool isLinked() const;
    };

}


#endif //BLACKENGINE_SHADERPROGRAM_H
