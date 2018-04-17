//
// Created by popof on 16.04.2018.
//

#include "glfwWindowFactory.h"
#include <memory>
#include "glfwWindow.h"

namespace black::ui {

    std::shared_ptr<Window> glfwWindowFactory::create() {
        return std::make_shared<glfwWindow>(
                this->title, this->width, this->height, this->mode,
                               this->isMaximized, this->isMinimized);
    }

    std::string glfwWindowFactory::getName() {
        return "GLFW Window Factory";
    }

}
