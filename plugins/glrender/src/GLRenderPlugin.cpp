//
// Created by popof on 16.04.2018.
//

#include "GLRenderPlugin.h"

#include <iostream>
#include <memory>
#include <core/Core.h>

using namespace std;

namespace black {

    std::string GLRenderPlugin::getName() {
        return std::string("OpenGL Render Plugin");
    }

    void GLRenderPlugin::install() {

    }

    void GLRenderPlugin::initialize() {
        cout << "initialize GLRenderPlugin!" << endl;
    }

    void GLRenderPlugin::shutdown() {
        cout << "shutdown GLRenderPlugin!" << endl;
    }

    void GLRenderPlugin::uninstall() {
        cout << "uninstall GLRenderPlugin!" << endl;
    }
}