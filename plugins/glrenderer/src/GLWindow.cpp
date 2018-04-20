//
// Created by popof on 20.04.2018.
//

#include "GLWindow.h"
#include <memory>

namespace black::ui {
    GLWindow::GLWindow(std::shared_ptr<render::GLContext> context) : Window(context) {
    }
}