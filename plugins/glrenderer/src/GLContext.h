//
// Created by popof on 20.04.2018.
//

#ifndef BLACKENGINE_GLCONTEXT_H
#define BLACKENGINE_GLCONTEXT_H

#include <string>
#include <core/render/Context.h>

namespace black::render {

    class GLContext : public Context {
    public:
        virtual int getMajorVersion();
        virtual int getMinorVersion();
        virtual std::string getVendorString();
        virtual std::string getRendererDeviceName();
    };
}


#endif //BLACKENGINE_GLCONTEXT_H
