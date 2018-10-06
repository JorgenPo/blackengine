//
// Created by popof on 29.09.2018.
//

#include "OpenGLRenderSystem.h"

namespace black {

    OpenGLRenderSystem::OpenGLRenderSystem() {
        this->logger = Logger::Get("OpenGLRenderSystem");
    }

    std::string OpenGLRenderSystem::getName() const {
        return std::string("OpenGL");
    }

    void OpenGLRenderSystem::initialize(std::string title, int width, int height, bool isFullScreen) {
        this->logger->trace("Initialization");

        this->logger->info("Using OpenGL 3.3 Core profile");

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef BLACK_PLATFORM_MACOSX
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        this->window = std::make_shared<GLFWWindow>(std::move(title), width, height, isFullScreen);
        this->window->setRenderTargetCurrent();

        // Init GLAD
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            this->logger->critical("Failed to init OpenGL Context");
            glfwTerminate();
            throw RenderSystemInitializationException("Failed to initialize OpenGL Context");
        }
    }

    void OpenGLRenderSystem::shutdown() {
        this->logger->trace("Shutdown");

        glfwTerminate();
    }

    std::shared_ptr<RendererInterface> OpenGLRenderSystem::getRenderer() {
        return nullptr;
    }

    OpenGLRenderSystem::~OpenGLRenderSystem() {
        this->logger->trace("Destructor!");
    }

    std::shared_ptr<AbstractRenderWindow> OpenGLRenderSystem::getRenderWindow() {
        return this->window;
    }
}