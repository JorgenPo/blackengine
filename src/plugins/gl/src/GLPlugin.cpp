//
// Created by popof on 27.09.2018.
//

#include <Engine.h>
#include "GLPlugin.h"
#include "OpenGLRenderSystem.h"

namespace black {

    std::shared_ptr<Logger> GLPlugin::logger;

    std::string GLPlugin::getName() {
        return std::string("GLPlugin");
    }

    void GLPlugin::install() {
        auto renderSystem = std::make_shared<OpenGLRenderSystem>();
        Engine::RegisterRenderSystem(renderSystem);
    }

    void GLPlugin::initialize() {
    }

    void GLPlugin::shutdown() {
    }

    void GLPlugin::uninstall() {
    }

    GLPlugin::GLPlugin() {
        logger = Logger::Get("GLPlugin");
    }
}