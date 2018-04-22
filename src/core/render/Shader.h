//
// Created by popof on 22.04.2018.
//

#ifndef BLACKENGINE_SHADER_H
#define BLACKENGINE_SHADER_H

#include <string>
#include <core/Exception.h>

namespace black::render {

    class ShaderCompileException : public Exception {
    public:
        explicit ShaderCompileException(std::string message);
    };

    /**
     * A gpu program class
     */
    class Shader {
    public:
        enum class Type {
            VERTEX,
            FRAGMENT,
            GEOMETRY,
        };

    protected:
        std::string source;
        Type type;
        bool compiled;

    public:
        Shader(const std::string &code, Type type);

        /**
         * Compiles a shader.
         *
         * @throws ShaderCompileException If shader compiled with errors
         */
        virtual void compile() = 0;

        bool isCompiled();

        /**
         * Returns implementation specific pointer
         *
         * @return
         */
        virtual void *getImplementation() = 0;

        const std::string &getSource() const;

        void setSource(const std::string &source);

        Type getType() const;
    };
}


#endif //BLACKENGINE_SHADER_H
