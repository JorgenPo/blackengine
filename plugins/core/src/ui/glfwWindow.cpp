/**
*  BlackEngine - all rights are reserved.
*  3D Game Engine
*  Created by Breezesoftware 
**/

#include <string>
#include <core/ui/Window.h>
#include <cmath>
#include "glfwWindow.h"

namespace black::ui {

    glfwWindow::glfwWindow(const std::string &title, int width, int height, Window::Mode mode, bool isMaximized,
                           bool isMinimized) : Window(title, width, height, mode, isMaximized, isMinimized)
    {
        if (!glfwInit()) {
            throw WindowInitializationException("Failed to init glfw library");
        }

        auto window = glfwCreateWindow(this->width, this->height, this->title.c_str(), nullptr, nullptr);
        this->window = std::shared_ptr<GLFWwindow>(window, glfwDestroyWindow);

        if (this->window == nullptr) {
            glfwTerminate();
            throw WindowInitializationException("Failed to create glfw window");
        }

        glfwMakeContextCurrent(this->window.get());
    }

    void glfwWindow::initialize() {

    }

    glfwWindow::~glfwWindow() {
        glfwTerminate();
    }

    int glfwWindow::run() {
        static double t = 0;

        while (!glfwWindowShouldClose(window.get())) {
            glClearColor(sin(t), cos(t), sin(t) * 2 * cos(t), 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            glfwSwapBuffers(window.get());
            glfwPollEvents();
            t += 0.0001;
        }
    }

}