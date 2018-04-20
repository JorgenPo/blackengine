//
// Created by popof on 20.04.2018.
//

#include "GLContext.h"
#include <GLFW/glfw3.h>

namespace black::render {

    int GLContext::getMajorVersion() {
        int version;
        glGetIntegerv(GLFW_VERSION_MAJOR, &version);

        return version;
    }

    int GLContext::getMinorVersion() {
        int version;
        glGetIntegerv(GLFW_VERSION_MINOR, &version);

        return version;
    }

    std::string GLContext::getVendorString() {
        return reinterpret_cast<const char*>(glGetString(GL_VENDOR));
    }

    std::string GLContext::getRendererDeviceName() {
        return reinterpret_cast<const char*>(glGetString(GL_RENDER));
    }
}