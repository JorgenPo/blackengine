//
// Created by popof on 16.04.2018.
//

#ifndef BLACKENGINE2018_GLFWWINDOWFACTORY_H
#define BLACKENGINE2018_GLFWWINDOWFACTORY_H

#include <core/ui/WindowFactory.h>

namespace black::ui {

    /**
     * Responsible for creating glfw windows
     */
    class glfwWindowFactory : public WindowFactory {
    public:
        std::shared_ptr<Window> create() override;

        std::string getName() override;
    };

}


#endif //BLACKENGINE2018_GLFWWINDOWFACTORY_H
