//
// Created by popof on 22.04.2018.
//

#ifndef BLACKENGINE_SHADER_H
#define BLACKENGINE_SHADER_H

#include <CommonHeaders.h>

namespace black {

    class BLACK_EXPORTED ShaderCompileException : public Exception {
    public:
        explicit ShaderCompileException(std::string message);
    };

    /**
     * A gpu program class
     */
    class BLACK_EXPORTED Shader {
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

        const std::string &getSource() const;

        void setSource(const std::string &source);

        Type getType() const;

        /**
         * Returns implementation specific pointer
         *
         * @return pointer to the shader implementation
         */
        virtual void *getImplementation() = 0;
    };
}


#endif //BLACKENGINE_SHADER_H
