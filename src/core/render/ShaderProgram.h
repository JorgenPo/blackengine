//
// Created by popof on 22.04.2018.
//

#ifndef BLACKENGINE_SHADERPROGRAM_H
#define BLACKENGINE_SHADERPROGRAM_H

#include <memory>
#include "Shader.h"

namespace black::render {

    class ShaderProgramLinkException : public Exception {
    public:
        explicit ShaderProgramLinkException(const std::string &message);
    };

    class ShaderProgramInvalidShaderTypeException : public Exception {
    public:
        explicit ShaderProgramInvalidShaderTypeException(const std::string &message);
    };

    class ShaderProgramNotLinkedException : public Exception {
    public:
        ShaderProgramNotLinkedException();
    };

    /**
     * Shader program
     */
    class ShaderProgram : public resources::Resource {
    protected:
        std::shared_ptr<Shader> vertexShader;
        std::shared_ptr<Shader> fragmentShader;
        std::shared_ptr<Shader> geometryShader;

        bool linked;
    public:
        /**
         * Loads a program from file and tries to compile
         * all shaders and link the program.
         * So, after this you can use program.
         *
         * @param fileName
         * @return
         */
        static std::shared_ptr<ShaderProgram> fromFile(const std::string &fileName);

        ShaderProgram();
        ShaderProgram(const std::shared_ptr<Shader> &vertexShader, const std::shared_ptr<Shader> &fragmentShader,
                      const std::shared_ptr<Shader> &geometryShader = std::shared_ptr<Shader>());

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
        virtual void addUniformVariable(const std::string &name) = 0;

        virtual void setUniformVariable(const std::string &name, int value) = 0;
        virtual void setUniformVariable(const std::string &name, float value) = 0;
        virtual void setUniformVariable(const std::string &name, bool value) = 0;
        virtual void setUniformVariable(const std::string &name, double value) = 0;
        virtual void setUniformVariable(const std::string &name, std::array<float, 4> value) = 0;
        virtual void setUniformVariable(const std::string &name, std::array<float, 3> value) = 0;
        virtual void setUniformVariable(const std::string &name, std::array<float, 2> value) = 0;

        const std::shared_ptr<Shader> &getVertexShader() const;
        const std::shared_ptr<Shader> &getFragmentShader() const;
        const std::shared_ptr<Shader> &getGeometryShader() const;

        void setVertexShader(const std::shared_ptr<Shader> &vertexShader);
        void setFragmentShader(const std::shared_ptr<Shader> &fragmentShader);
        void setGeometryShader(const std::shared_ptr<Shader> &geometryShader);

        bool isLinked() const;
    };

}


#endif //BLACKENGINE_SHADERPROGRAM_H
