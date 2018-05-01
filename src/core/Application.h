#ifndef BLACKENGINE2018_APPLICATION_H
#define BLACKENGINE2018_APPLICATION_H

#include <memory>
#include <core/scene/Scene.h>

#include "ui/Window.h"
#include "Core.h"


namespace black {

    class ApplicationNotInitializedException : public Exception {
    public:
        ApplicationNotInitializedException();
    };

    class ApplicationInitializationException : public Exception {
    public:
        explicit ApplicationInitializationException(const std::string &message);
    };

    /**
     * Main class of application
     */
    class Application : public ui::WindowEventListener {
    protected:
        const std::string MAIN_SCENE_NAME = "Main Scene";

        std::shared_ptr<ui::Window> mainWindow;
        std::shared_ptr<scene::Scene> mainScene;
        std::shared_ptr<Camera> mainCamera;

        Core *core;

        bool isInitialized;

        std::string windowTitle;
        int windowWidth;
        int windowHeight;

    public:
        /* Initialize application. Constructor calls initialize() method
         * of subclasses
         */
        Application(std::string windowTitle, int windowWidth, int windowHeight);
        Application();

        virtual ~Application();
        virtual void initialize();
        virtual void processInput();

        /**
         * Runs the application. Shows the window.
         * User must set the window before run application
         */
        virtual int run();

        /**
         * Updates a logic. Called every frame.
         */
        virtual void update();
    private:
        void setDefaultRenderer();
        void setMainWindow();
        void setMainScene();

        void setMainCamera();
    };

}


#endif //BLACKENGINE2018_APPLICATION_H
