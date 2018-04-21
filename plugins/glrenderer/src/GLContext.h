//
// Created by popof on 20.04.2018.
//

#ifndef BLACKENGINE_GLCONTEXT_H
#define BLACKENGINE_GLCONTEXT_H

#include <string>
#include <core/render/Context.h>

namespace black::render {

    struct GLVersion {
        int major;
        int minor;
        int revision;
    };

    class GLContext : public Context {
        GLVersion version;
    public:
        GLContext();

        virtual int getGLMajorVersion();
        virtual int getGLMinorVersion();
        virtual int getGLRevisionVersion();
        virtual GLVersion getGLVersion();
        virtual std::string getGLVersionString();
        virtual std::string getGLVendorString();
        virtual std::string getGLRendererDeviceName();

        void initializeContext() override;
    };
}


#endif //BLACKENGINE_GLCONTEXT_H
