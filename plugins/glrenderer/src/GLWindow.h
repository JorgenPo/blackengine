//
// Created by popof on 20.04.2018.
//

#ifndef BLACKENGINE_GLWINDOW_H
#define BLACKENGINE_GLWINDOW_H

#include <core/ui/Window.h>
#include <bits/shared_ptr.h>
#include "GLContext.h"

namespace black::ui {

    /**
     * Window capable to work with OpenGL renderer
     */
    class GLWindow : public Window {

    public:
        explicit GLWindow(std::shared_ptr<render::GLContext> context);

    };

}


#endif //BLACKENGINE_GLWINDOW_H
