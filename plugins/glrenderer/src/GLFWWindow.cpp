/**
*  BlackEngine - all rights are reserved.
*  3D Game Engine
*  Created by Breezesoftware 
**/

#include <string>
#include <core/ui/Window.h>
#include <cmath>
#include "GLFWWindow.h"

namespace black::ui {

    GLFWWindow::GLFWWindow(const std::string &title, int width, int height, Window::Mode mode, bool isMaximized,
                           bool isMinimized) : GLWindow(std::shared_ptr<GLFWWindow>(this))
    {
        this->title = title;
        this->width = width;
        this->height = height;
        this->mode = mode;
        this->isMaximized = isMaximized;
        this->isMinimized = isMinimized;
    }

    void GLFWWindow::initialize() {
        if (!glfwInit()) {
            throw WindowInitializationException("Failed to init glfw library");
        }

        auto window = glfwCreateWindow(this->width, this->height, this->title.c_str(), nullptr, nullptr);
        this->window = std::shared_ptr<GLFWwindow>(window, glfwDestroyWindow);

        if (this->window == nullptr) {
            glfwTerminate();
            throw WindowInitializationException("Failed to create glfw mainWindow");
        }
    }

    GLFWWindow::~GLFWWindow() {
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
}