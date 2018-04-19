#ifndef BLACKENGINE2018_APPLICATION_H
#define BLACKENGINE2018_APPLICATION_H

#include <memory>
#include <core/scene/Scene.h>

#include "ui/Window.h"


namespace black {
    /**
     * Main class of application
     */
    class Application {
    protected:
        std::shared_ptr<ui::Window> window;
        std::shared_ptr<scene::Scene> mainScene;

    public:
        /* Initialize application. Constructor calls initialize() method
         * of subclasses
         */
        Application();

        virtual ~Application();

        virtual void initialize();

        /**
         * Runs the application. Shows the window.
         * User must set the window before run application
         */
        virtual int run();
    };

}


#endif //BLACKENGINE2018_APPLICATION_H
