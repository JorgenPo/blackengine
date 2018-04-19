//
// Created by popof on 15.04.2018.
//
#include "Core.h"

#include <set>
#include <core/os/windows/WindowsSharedLibrary.h>
#include <sstream>

namespace black {

    Core* Core::instance = nullptr;

    CoreInitializationException::CoreInitializationException(const std::string &message) : Exception(message) {}
    UnknownPlatformException::UnknownPlatformException() : Exception("Unknown target platform") {}
    RendererNotSetException::RendererNotSetException() : Exception("No renderers was loaded. Please, set up a renderer manually.") {}
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
        // Responsible for manage plugins
        this->pluginManager = std::make_unique<PluginManager>();

        determineTargetPlatform();
    }

    const std::unique_ptr<PluginManager> &Core::getPluginManager() const {
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
        // Load core plugin
        try {
            this->pluginManager->loadPlugin(CORE_PLUGIN_NAME);
        } catch(const PluginNotFoundException &e) {
            std::string message = "Failed to load core plugin. Check ";
            message += CORE_PLUGIN_NAME + " shared library exist in application directory";

            throw CoreInitializationException(message);
        }
    }

    void Core::render() {
        if (this->currentRenderer == nullptr) {
            throw RendererNotSetException();
        }

        //this->currentRenderer->renderToAllTargets();
    }

    void Core::registerScenePrototype(std::shared_ptr<scene::Scene> prototype) {
        this->scenePrototypes.push_back(prototype);
    }

    std::shared_ptr<scene::Scene> Core::createScene(std::string prototypeName) {
        for (const auto &prototype : this->scenePrototypes) {
            if (prototype->getPrototypeName() == prototypeName) {
                return std::shared_ptr<scene::Scene>(prototype->copy());
            }
        }

        throw ScenePrototypeNotFoundException(prototypeName);
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

        if (exist.second == true) {
            throw RendererAlreadyExistException(newRenderer->getName());
        }
    }

    const Core::RendererSet &Core::getAvailableRenderers() {
        return this->renderers;
    }
}
