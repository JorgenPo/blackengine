//
// Created by popof on 02.10.2018.
//

#ifndef BLACKENGINE_GAMEAPPLICATION_H
#define BLACKENGINE_GAMEAPPLICATION_H

#include <CommonHeaders.h>
#include <render/AbstractRenderWindow.h>
#include <render/RendererInterface.h>
#include "AbstractApplication.h"

namespace black {

    /**
     * Single window and real time updating application.
     */
    class BLACK_EXPORTED GameApplication : public AbstractApplication {
    protected:
        std::shared_ptr<AbstractRenderWindow> window;
        std::shared_ptr<RendererInterface> renderer;

    public:
        /**
         * Init application with a given name and a game window properties
         *
         * @param name              Name of the application
         * @param windowWidth       Application window width
         * @param windowHeight      Application window height
         * @param isFullScreen      Is the application window should be shown as fullscreen
         *
         * @throws ApplicationInitializationException If failed to init a window
         */
        explicit GameApplication(const std::string &name, int windowWidth, int windowHeight, bool isFullScreen);

    private:
        void run() override;

    protected:
        void init() override;
    };
}


#endif //BLACKENGINE_GAMEAPPLICATION_H
