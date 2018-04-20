//
// Created by popof on 16.04.2018.
//

#include "GLRendererPlugin.h"
#include "GLRenderer.h"

#include <iostream>
#include <memory>
#include <core/Core.h>

using namespace std;

namespace black {

    std::string GLRendererPlugin::getName() {
        return std::string("OpenGL Renderer Plugin");
    }

    void GLRendererPlugin::install() {
        auto core = Core::getInstance();
        core->registerRenderer(std::make_shared<render::GLRenderer>());
    }

    void GLRendererPlugin::initialize() {
        cout << "initialize GLRendererPlugin!" << endl;
    }

    void GLRendererPlugin::shutdown() {
        cout << "shutdown GLRendererPlugin!" << endl;
    }

    void GLRendererPlugin::uninstall() {
        cout << "uninstall GLRendererPlugin!" << endl;
    }
}