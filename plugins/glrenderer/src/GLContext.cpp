//
// Created by popof on 20.04.2018.
//

#include "GLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace black::render {

    GLContext::GLContext() : version() {
    }

    int GLContext::getGLMajorVersion() {
        return this->version.major;
    }

    int GLContext::getGLMinorVersion() {
        return this->version.minor;
    }

    int GLContext::getGLRevisionVersion() {
        return this->version.revision;
    }

    std::string GLContext::getGLVendorString() {
        auto string = reinterpret_cast<const char*>(glGetString(GL_VENDOR));

        if (string == nullptr) {
            string = "Unknown vendor";
        }

        return string;
    }

    std::string GLContext::getGLRendererDeviceName() {
        auto string = reinterpret_cast<const char*>(glGetString(GL_RENDERER));

        if (string == nullptr) {
            string = "Unknown device name";
        }

        return string;
    }

    GLVersion GLContext::getGLVersion() {
        return this->version;
    }

    std::string GLContext::getGLVersionString() {
        static auto string = glfwGetVersionString();

        return string;
    }

    // Called after creating context and making it current
    void GLContext::initializeContext() {
        this->setContextCurrent();

        glfwGetVersion(&this->version.major, &this->version.minor, &this->version.revision);
        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
            throw ContextInitializationException("Failed to load GL loader using glad");
        }
    }
}