/**
*  BlackEngine - all rights are reserved.
*  3D Game Engine
*  Created by Breezesoftware 
**/

#ifndef BLACKENGINE2018_GLFWWINDOW_H
#define BLACKENGINE2018_GLFWWINDOW_H

#include <GLFW/glfw3.h>

#include <config/config.h>
#include <core/ui/Window.h>

#include <string>
#include <memory>

namespace black::ui {

    /**
     * A window working with GLFW library
     */
    class glfwWindow : public Window {
        std::shared_ptr<GLFWwindow> window;

    public:
        glfwWindow(const std::string &title, int width, int height,
                   Mode mode = Mode::NORMAL, bool isMaximized = false, bool isMinimized = false);

        virtual ~glfwWindow();

        void initialize() override;

        int run() override;
    };

}


#endif //BLACKENGINE2018_GLFWWINDOW_H
