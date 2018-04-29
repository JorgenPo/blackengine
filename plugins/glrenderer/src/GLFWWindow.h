/**
*  BlackEngine - all rights are reserved.
*  3D Game Engine
*  Created by Breezesoftware 
**/

#ifndef BLACKENGINE2018_GLFWWINDOW_H
#define BLACKENGINE2018_GLFWWINDOW_H

#include "GLIncludes.h"

#include <string>
#include <memory>

#include <config/config.h>
#include "GLContext.h"
#include "GLWindow.h"

namespace black::ui {

    /**
     * A window working with GLFW library. That type of window implement
     * renderer context interface also.
     */
    class GLFWWindow : public GLWindow, public render::GLContext {
        std::shared_ptr<GLFWwindow> window;

    public:
        explicit GLFWWindow(std::string name, const std::string &title = "", int width = 800, int height = 600,
                   Mode mode = Mode::NORMAL, bool isMaximized = false, bool isMinimized = false);

        virtual ~GLFWWindow();

        void initialize() override;
        bool isWindowShouldClose() override;
        void pollEvents() override;

        bool isKeyPressed(InputKey key) override;
        bool isKeyPressed(int key) override;

        void resize(int width, int height) override;

        /* Render target interface */
        std::string getRenderTargetName() override;
        void updateRenderTarget() override;

        /* Context interface */
        void setContextCurrent() override;
        bool isContextCurrent() override;

        void setCallbacks();
    };

}


#endif //BLACKENGINE2018_GLFWWINDOW_H
