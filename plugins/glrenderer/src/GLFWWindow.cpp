/**
*  BlackEngine - all rights are reserved.
*  3D Game Engine
*  Created by Breezesoftware 
**/

#include <string>
#include <core/ui/Window.h>
#include <cmath>
#include <iostream>
#include <core/ui/WindowEventEmitter.h>
#include "GLFWWindow.h"

namespace black::ui {

    GLFWWindow::GLFWWindow(std::string name, const std::string &title, int width, int height, Window::Mode mode, bool isMaximized,
                           bool isMinimized) : GLWindow(std::move(name), std::shared_ptr<GLFWWindow>(this))
    {
        this->title = title;
        this->width = width;
        this->height = height;
        this->mode = mode;
        this->isMaximized = isMaximized;
        this->isMinimized = isMinimized;
    }

    void GLFWWindow::initialize() {
        Window::initialize();

        if (!glfwInit()) {
            throw WindowInitializationException("Failed to init glfw library");
        }

        // TODO: think where it can be
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        auto window = glfwCreateWindow(this->width, this->height, this->title.c_str(), nullptr, nullptr);
        this->window = std::shared_ptr<GLFWwindow>(window, glfwDestroyWindow);

        if (this->window == nullptr) {
            glfwTerminate();
            throw WindowInitializationException("Failed to create glfw context");
        }

        // Store this pointer as additional window data
        glfwSetWindowUserPointer(this->window.get(), this);

        this->initializeContext();

        // Set viewport to hold all window
        glViewport(0, 0, this->width, this->height);

        // Register resize callback
        glfwSetFramebufferSizeCallback(this->window.get(), [](GLFWwindow *window, int width, int height) {
            auto glfwWindow = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
            glfwWindow->resize(width, height);
        });

        // Required to get rid of GL_INVALID_ENUM error
        glGetError();
    }

    GLFWWindow::~GLFWWindow() {
        this->window.reset();
        glfwTerminate();
    }

    void GLFWWindow::setContextCurrent() {
        glfwMakeContextCurrent(this->window.get());
    }

    bool GLFWWindow::isContextCurrent() {
        return glfwGetCurrentContext() == this->window.get();
    }

    std::string GLFWWindow::getRenderTargetName() {
        return this->title;
    }

    void GLFWWindow::updateRenderTarget() {
        /* Updates */
        glfwSwapBuffers(this->window.get());
    }

    bool GLFWWindow::isWindowShouldClose() {
        return glfwWindowShouldClose(window.get()) > 0;
    }

    void GLFWWindow::pollEvents() {
        glfwPollEvents();
    }

    void GLFWWindow::resize(int width, int height) {
        Window::resize(width, height);
        glViewport(0, 0, width, height);

        this->emitWindowSizeChanged(this, width, height);
    }

    bool GLFWWindow::isKeyPressed(InputKey key) {
        // GLFW KEYS AND InputKey enum are fully compatible
        return glfwGetKey(this->window.get(), static_cast<int>(key)) == GLFW_PRESS;
    }
}