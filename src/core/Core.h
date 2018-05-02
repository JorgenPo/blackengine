//
// Created by popof on 15.04.2018.
//

#ifndef BLACKENGINE2018_CORE_H
#define BLACKENGINE2018_CORE_H

#include <memory>
#include <vector>
#include <set>
#include <list>

#include <config/config.h>
#include <core/render/Renderer.h>
#include <core/scene/Scene.h>
#include <core/resources/ResourceManager.h>
#include <core/parsers/ModelParser.h>
#include <core/performance/PerformanceCounter.h>


#include "PluginManager.h"

namespace black {

    class NotImplementedException : public Exception {
    public:
        NotImplementedException(const std::string &what);
    };

    class CoreInitializationException : public Exception {
    public:
        explicit CoreInitializationException(const std::string &message);
    };

    class UnknownPlatformException : public Exception {
    public:
        UnknownPlatformException();
    };

    class RendererNotSetException : public Exception {
    public:
        RendererNotSetException();
    };

    class SceneNotSetException : public Exception {
    public:
        SceneNotSetException();
    };

    class ScenePrototypeAlreadyExistException : public Exception {
    public:
        explicit ScenePrototypeAlreadyExistException(const std::string &prototypeName);
    };

    class ScenePrototypeNotFoundException : public Exception {
    public:
        explicit ScenePrototypeNotFoundException(const std::string &sceneType);
    };

    class SceneAlreadyExistException : public Exception {
    public:
        explicit SceneAlreadyExistException(const std::string &name);
    };

    class RendererAlreadyExistException : public Exception {
    public:
        explicit RendererAlreadyExistException(const std::string &name);
    };

    class SceneNotFoundException : public Exception {
    public:
        explicit SceneNotFoundException(const std::string &name);
    };

    class CameraPrototypeNotFound : public Exception {
    public:
        explicit CameraPrototypeNotFound(const std::string &name);
    };

    enum class Platform {
        UNKNOWN,
        WINDOWS,
        LINUX,
        MACOSX
    };

    /**
     * Responsible for register components and provide
     *  components runtime
     *
     *  @singleton
     */
    class Core {
        using PluginsMap = std::map<std::string, std::shared_ptr<Plugin>>;
        using ScenePrototypeList = std::list<std::shared_ptr<scene::Scene>>;
        using SceneMap = std::map<std::string, std::shared_ptr<scene::Scene>>;
        using RendererSet = std::set<std::shared_ptr<render::Renderer>>;
        using ModelParsersMap = std::map<std::string, std::shared_ptr<parsers::ModelParser>>;
        using CameraPrototypeMap = std::map<std::string, std::shared_ptr<Camera>>;

    private:
        static Core *instance;

        const std::string CORE_PLUGIN_NAME = "CorePlugin";
        const std::string GL_RENDERER_PLUGIN_NAME = "GLRendererPlugin";

        Platform platform;

        PluginsMap plugins;
        RendererSet renderers;
        ScenePrototypeList scenePrototypes;
        CameraPrototypeMap cameraPrototypes;
        SceneMap scenes;
        ModelParsersMap modelParsers;

        std::unique_ptr<PluginManager> pluginManager;
        std::unique_ptr<resources::ResourceManager> resourceManager;
        std::shared_ptr<render::Renderer> currentRenderer;
        std::shared_ptr<scene::Scene> currentScene;
        std::shared_ptr<ui::Window> eventWindow;

        std::shared_ptr<performance::PerformanceCounter> performanceCounter;

        Core();
        ~Core() = default;
    public:
        Core(Core const&) = delete;
        Core& operator=(Core const&) = delete;

        static Core* getInstance() {
            if (instance == nullptr) {
                instance = new Core();
            }

            return instance;
        }

        static const std::unique_ptr<PluginManager> &GetPluginManager() {
            return instance->getPluginManager();
        }

        static const std::unique_ptr<resources::ResourceManager> &GetResourceManager() {
            return instance->getResourceManager();
        }

        /**
         * Initialize blackengine core
         * Application must call this method.
         * Loads plugins, set up runtime systems.
         *
         * @throws CoreInitializationException When core hasn't init successfully.
         * The message contains a problem description
         */
        void initialize();

        /**
         * Returns a pointer to plugin manager instance
         * @return PluginManager pointer
         */
        const std::unique_ptr<PluginManager> &getPluginManager() const;

        /**
         * Returns a pointer to resource manager instance
         * @return ResourceManager pointer
         */
        const std::unique_ptr<resources::ResourceManager> &getResourceManager() const;

        /**
         * Initialize concrete subclass of SharedLibrary suitable for user
         * platform
         *
         * @param name Library name
         *
         * @throws UnknownPlatformException If failed to determine runtime platform
         * @return Pointer to library object
         */
        std::shared_ptr<SharedLibrary> getPlatformLibrary(std::string name);

        /**
         * Returns platform enum value
         * @return Target platform or Platform::UNKNOWN
         */
        Platform getPlatform() const;

        /**
         * Register external plugin
         * @param plugin Plugin to be registered
         */
        void registerPlugin(std::shared_ptr<Plugin> plugin);

        /**
         * Unregister external plugin
         * @param plugin Plugin to be unregistered
         */
        void unregisterPlugin(std::shared_ptr<Plugin> plugin);

        /**
         * Register a renderer in core
         *
         * @param renderer Renderer
         */
        void registerRenderer(std::shared_ptr<render::Renderer> renderer);

        const RendererSet &getAvailableRenderers();

        void setRenderer(std::shared_ptr<render::Renderer>);
        std::shared_ptr<render::Renderer> getCurrentRenderer();

        /**
         * Set main event window that handles user input events
         * @param window
         */
        void setEventWindow(std::shared_ptr<ui::Window> window);

        std::shared_ptr<ui::Window> getEventWindow();

        /**
         * Register a scene type prototype.
         *
         * @throws ScenePrototypeAlreadyExistException if type with that name was already registered
         * @param prototype Pointer to a scene class object. That object will be
         * copied every time user creates scene with this type
         */
        void registerScenePrototype(std::shared_ptr<scene::Scene> prototype);

        /**
         * Creates scene with given prototypeName string.
         * Looks in scenePrototypes for prototype with name prototypeName.
         *
         * @param prototypeName Name of scene prototype
         *
         * @throws ScenePrototypeNotFoundException if no such scene prototype was registered
         * @return
         */
        std::shared_ptr<scene::Scene> createSceneWithType(std::string prototypeName);

        /**
         * Add scene to scene list with given name.
         *
         * @param scene A scene
         * @param name Name for scene
         */
        void addScene(std::shared_ptr<scene::Scene> scene, std::string name);

        /**
         * Removes a scene with given name
         *
         * @param name A scene name
         */
        void removeScene(std::string name);

        /**
         * Registers a model parser prototype for a given extension
         *
         * @param extension Extension name for this prototype
         * @param prototype Prototype
         */
        void registerModelParserPrototype(std::string extension, std::shared_ptr<parsers::ModelParser> prototype);

        std::shared_ptr<parsers::ModelParser> getModelParserForExtension(std::string extension);

        /**
         * Set scene with given name current
         *
         * @param name Scene name
         */
        void setCurrentScene(std::string name);

        /**
         * Renders a new frame
         */
        void renderFrame();

        /**
         * Registers a camera prototype
         *
         * @param name Camera type name
         * @param prototype Camera copyable prototype
         */
        void registerCameraPrototype(std::string name, std::shared_ptr<Camera> prototype);

        /**
         * Creates a camera with given prototypeName
         *
         * @param name Name of registered camera prototype
         * @return Camera object with desired prototype
         */
        std::shared_ptr<Camera> createCamera(std::string prototypeName);

        /**
         * Returns the performance counter
         *
         * @return performance::PerformanceCounter
         */
        const std::shared_ptr<performance::PerformanceCounter> &getPerformanceCounter() const;

    private:
        /**
         * Set up platform information
         */
        void determineTargetPlatform();
    };

}
#endif //BLACKENGINE2018_CORE_H
