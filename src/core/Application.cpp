/**
*  BlackEngine - all rights are reserved.
*  3D Game Engine
*  Created by Breezesoftware
**/

#include "Application.h"
#include "Core.h"
#include "Exception.h"

#include <utility>

namespace black {

    ApplicationNotInitializedException::ApplicationNotInitializedException()
            : Exception("Application must be initialized before run. Call initialize method") {}

    ApplicationInitializationException::ApplicationInitializationException(const std::string &message)
            : Exception(message) {}


    Application::Application() : core(Core::getInstance()), isInitialized(false), windowTitle("BlackEngine application"),
                                 windowWidth(800), windowHeight(600)
    {

    }

    Application::Application(std::string title, int windowWidth, int windowHeight)
            : core(Core::getInstance()), isInitialized(false), windowTitle(std::move(title)),
              windowWidth(windowWidth), windowHeight(windowHeight) {

    }

    Application::~Application() = default;


    /**
     * Application loop
     *
     * @return Result code
     */
    int Application::run() {
        if (!isInitialized) {
            throw ApplicationNotInitializedException();
        }

        if (this->mainWindow == nullptr) {
            throw Exception("Window has not been set up");
        }

        while (!this->mainWindow->isWindowShouldClose() &&
               !(this->mainWindow->isKeyPressed(InputKey::KEY_ESCAPE))) {
            this->processInput();
            this->update();
            this->core->renderFrame();
            this->mainWindow->pollEvents();
        }

        return 0;
    }

    void Application::initialize() {
        setMainWindowAndRenderer();
        setDefaultRenderer();
        setMainScene();
        setMainCamera();

        // Enable backface culling
        //this->core->getCurrentRenderer()->enableFaceCulling(render::Culling::BACK);

        this->isInitialized = true;
    }

    void Application::setDefaultRenderer() {
        auto renderers = this->core->getAvailableRenderers();

        for (const auto &renderer : renderers) {
            this->core->setRenderer(renderer);
            return;
        }

        throw ApplicationInitializationException("No available renderers found");
    }

    void Application::setMainWindowAndRenderer() {
        auto renderers = this->core->getAvailableRenderers();

        if (renderers.empty()) {
            throw ApplicationInitializationException("No available renderers found");
        }

        auto firstRenderer = *(renderers.begin());

        // Create window for renderFrame using this renderer
        try {
            this->mainWindow = firstRenderer->createRendererWindow(this->windowTitle);
            this->mainWindow->setTitle(this->windowTitle);
            this->mainWindow->setWidth(this->windowWidth);
            this->mainWindow->setHeight(this->windowHeight);
            this->mainWindow->initialize();
        } catch(const Exception &e) {
            throw ApplicationInitializationException("Failed to init main window: " + e.getMessage());
        }

        this->core->setRenderer(firstRenderer);
        this->core->getCurrentRenderer()->addRenderTarget(this->mainWindow);

        // Listen for windows event
        this->mainWindow->listen(this);

        // Set main window as event capturing window
        this->core->setEventWindow(this->mainWindow);
    }

    void Application::setMainScene() {
        this->mainScene = this->core->createSceneWithType("Simple Scene");
        this->core->addScene(this->mainScene, MAIN_SCENE_NAME);
        this->core->setCurrentScene(MAIN_SCENE_NAME);
    }

    void Application::processInput() {
    }

    void Application::update() {

    }

    void Application::setMainCamera() {
        this->mainCamera = this->mainScene->createCamera("spectator");
        this->mainCamera->transform->setPosition({0.0f, 1.0f, 100.0f});
        this->mainCamera->setSoftness(0.1f);
    }
}