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
