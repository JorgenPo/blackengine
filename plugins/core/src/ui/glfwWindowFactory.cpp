//
// Created by popof on 16.04.2018.
//

#include "glfwWindowFactory.h"

namespace black::ui {

    std::shared_ptr<Window> glfwWindowFactory::create() {
        return std::shared_ptr<Window>();
    }

}
