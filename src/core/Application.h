#ifndef BLACKENGINE2018_APPLICATION_H
#define BLACKENGINE2018_APPLICATION_H

#include <memory>

#include "ui/Window.h"


namespace black::core::engine {
    /**
     * Main class of application
     */
    class Application {
    protected:
        std::shared_ptr<ui::Window> window;

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
        virtual void run();
    };

}


#endif //BLACKENGINE2018_APPLICATION_H
