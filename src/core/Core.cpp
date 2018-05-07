//
// Created by popof on 15.04.2018.
//
#include "Core.h"

#include <set>
#include <core/os/windows/WindowsSharedLibrary.h>
#include <sstream>
#include <utility>

namespace black {

    Core* Core::instance = nullptr;

    NotImplementedException::NotImplementedException(const std::string &what) : Exception() {
        std::stringstream stream;
        stream << what << " not implemented";
        this->message = stream.str();
    }

    CoreInitializationException::CoreInitializationException(const std::string &message) : Exception(message) {}
    UnknownPlatformException::UnknownPlatformException() : Exception("Unknown target platform") {}
    RendererNotSetException::RendererNotSetException()
            : Exception("No renderer was set. Please, set up a renderer before render frame") {}
    SceneNotSetException::SceneNotSetException()
            : Exception("No scene was set. Please, set up a scene before render frame") {}
    ScenePrototypeAlreadyExistException::ScenePrototypeAlreadyExistException(const std::string &prototypeName) : Exception() {
        std::stringstream stream;
        stream << "Scene prototype with name '" << prototypeName << "' already exist";
        this->message = stream.str();
    }
    ScenePrototypeNotFoundException::ScenePrototypeNotFoundException(const std::string &sceneType) : Exception() {
        std::stringstream stream;
        stream << "Scene prototype with name '" << sceneType << "' not found";
        this->message = stream.str();
    }
    CameraPrototypeNotFound::CameraPrototypeNotFound(const std::string &name) {
        std::stringstream stream;
        stream << "Camera prototype with name '" << name << "' not found";
        this->message = stream.str();
    }
    SceneAlreadyExistException::SceneAlreadyExistException(const std::string &name) : Exception() {
        std::stringstream stream;
        stream << "Scene with name '" << name << "' already exist";
        this->message = stream.str();
    }
    SceneNotFoundException::SceneNotFoundException(const std::string &name) : Exception() {
        std::stringstream stream;
        stream << "Scene with name '" << name << "' not found";
        this->message = stream.str();
    }
    RendererAlreadyExistException::RendererAlreadyExistException(const std::string &name) : Exception() {
        std::stringstream stream;
        stream << "Renderer with name '" << name << "' already exist";
        this->message = stream.str();
    }

    Core::Core() : platform(Platform::UNKNOWN) {
        // Initialize logger
        Logger::initialize();

        // Responsible for manage plugins
        this->pluginManager = std::make_shared<PluginManager>();

        // Responsible for manage resources
        this->resourceManager = std::make_shared<resources::ResourceManager>();

        // Responsible for measure fps and mpf
        this->performanceCounter = std::make_shared<performance::PerformanceCounter>();

        determineTargetPlatform();
    }

    const std::shared_ptr<PluginManager> &Core::getPluginManager() const {
        return pluginManager;
    }

    std::shared_ptr<SharedLibrary> Core::getPlatformLibrary(std::string name) {
        switch (this->platform) {
            case Platform::WINDOWS:
                return std::make_shared<os::WindowsSharedLibrary>(name);
            case Platform::LINUX:
                // TODO: LINUX
                return std::make_shared<os::WindowsSharedLibrary>(name);
            case Platform::MACOSX:
                // TODO: MACOSX
                return std::make_shared<os::WindowsSharedLibrary>(name);
            default:
                throw UnknownPlatformException();
        }
    }

    Platform Core::getPlatform() const {
        return platform;
    }

    void Core::determineTargetPlatform() {
#ifdef BLACK_PLATFORM_WINDOWS
        this->platform = Platform::WINDOWS;
#elif BLACK_PLATFORM_LINUX
        this->platform = Platform::LINUX;
#elif BLACK_PLATFORM_MACOSX
        this->platform = Platform::MACOSX;
#endif
    }

    void Core::registerPlugin(std::shared_ptr<Plugin> plugin) {
        plugin->install();
    }

    void Core::unregisterPlugin(std::shared_ptr<Plugin> plugin) {
        plugin->uninstall();
    }

    void Core::initialize() {
        try {
            // Load core plugin
            this->pluginManager->loadPlugin(CORE_PLUGIN_NAME);

            // Default opengl renderer
            this->pluginManager->loadPlugin(GL_RENDERER_PLUGIN_NAME);
        } catch(const PluginNotFoundException &e) {
            std::string message = "Failed to load core plugin. Check ";
            message += CORE_PLUGIN_NAME + " shared library exist in application directory";

            throw CoreInitializationException(message);
        }
    }

    void Core::renderFrame() {
        if (this->currentRenderer == nullptr) {
            throw RendererNotSetException();
        }

        if (this->currentScene == nullptr) {
            throw SceneNotSetException();
        }

        // Count performance
        this->performanceCounter->update();

        /* Updates camera position and rotation */
        auto camera = this->currentScene->getCurrentCamera();
        if (camera != nullptr) {
            camera->updateCamera();
            this->currentRenderer->setRendererView(camera);
        }

        auto objects = this->currentScene->getEntities();
        this->currentRenderer->renderToAllTargets(objects);
    }

    void Core::registerScenePrototype(const std::shared_ptr<scene::Scene> &prototype, std::string name) {
        this->scenePrototypes[std::move(name)] = prototype;
    }

    std::shared_ptr<scene::Scene> Core::createSceneWithType(std::string prototypeName) {
        if (this->scenePrototypes.find(prototypeName) == this->scenePrototypes.end()) {
            throw ScenePrototypeNotFoundException(prototypeName);
        }

        return std::shared_ptr<scene::Scene>(this->scenePrototypes[prototypeName]->copy());
    }

    void Core::addScene(std::shared_ptr<scene::Scene> newScene, std::string name) {
        if (this->scenes.find(name) != this->scenes.end()) {
            throw SceneAlreadyExistException(name);
        }

        this->scenes[name] = newScene;

        if (this->currentScene == nullptr) {
            this->currentScene = newScene;
        }
    }

    void Core::setCurrentScene(std::string name) {
        if (this->scenes.find(name) == this->scenes.end()) {
            throw SceneNotFoundException(name);
        }

        this->currentScene = this->scenes[name];
    }

    void Core::removeScene(std::string name) {
        this->scenes.erase(name);
    }

    void Core::registerRenderer(std::shared_ptr<render::Renderer> newRenderer) {
        auto exist = this->renderers.insert(newRenderer);

        // If no renderer was inserted
        if (!exist.second) {
            throw RendererAlreadyExistException(newRenderer->getName());
        }
    }

    const Core::RendererSet &Core::getAvailableRenderers() {
        return this->renderers;
    }

    void Core::setRenderer(std::shared_ptr<render::Renderer> renderer) {
        this->currentRenderer = std::move(renderer);
    }

    std::shared_ptr<render::Renderer> Core::getCurrentRenderer() {
        return this->currentRenderer;
    }

    const std::shared_ptr<resources::ResourceManager> &Core::getResourceManager() const {
        return resourceManager;
    }

    void Core::registerModelParserPrototype(std::string extension, std::shared_ptr<parsers::ModelParser> prototype) {
        this->modelParsers[extension] = std::move(prototype);
    }

    std::shared_ptr<parsers::ModelParser> Core::getModelParserForExtension(std::string extension) {
        if (this->modelParsers.find(extension) != this->modelParsers.end()) {
            return std::shared_ptr<parsers::ModelParser>(this->modelParsers[extension]->copy());
        }

        return nullptr;
    }

    void Core::registerCameraPrototype(std::string name, std::shared_ptr<Camera> prototype) {
        this->cameraPrototypes[name] = std::move(prototype);
    }

    std::shared_ptr<Camera> Core::createCamera(std::string prototypeName) {
        if (this->cameraPrototypes.find(prototypeName) == this->cameraPrototypes.end()) {
            throw CameraPrototypeNotFound(prototypeName);
        }

        return std::shared_ptr<Camera>(this->cameraPrototypes[prototypeName]->copy());
    }

    void Core::setEventWindow(std::shared_ptr<ui::Window> window) {
        this->eventWindow = window;
    }

    std::shared_ptr<ui::Window> Core::getEventWindow() {
        return this->eventWindow;
    }

    const std::shared_ptr<performance::PerformanceCounter> &Core::getPerformanceCounter() const {
        return performanceCounter;
    }
}
