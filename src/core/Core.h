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

    private:
        static Core *instance;

        const std::string CORE_PLUGIN_NAME = "CorePlugin";
        const std::string GL_RENDERER_PLUGIN_NAME = "GLRendererPlugin";

        Platform platform;

        PluginsMap plugins;
        RendererSet renderers;
        ScenePrototypeList scenePrototypes;
        SceneMap scenes;

        std::unique_ptr<PluginManager> pluginManager;
        std::shared_ptr<render::Renderer> currentRenderer;
        std::shared_ptr<scene::Scene> currentScene;

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

        /**
         * Initialize blackengine core
         * Application must call this method.
         * Loads plugins, set up runtime systems.
         *
         * @throws CoreInitializationException When core hasn't init successfully.
         * The message contains a problem description
         */
        void initialize();

        const std::unique_ptr<PluginManager> &getPluginManager() const;

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
         * Set scene with given name current
         *
         * @param name Scene name
         */
        void setCurrentScene(std::string name);

        /**
         * Renders a new frame
         */
        void renderFrame();

    private:
        /**
         * Set up platform information
         */
        void determineTargetPlatform();
    };

}
#endif //BLACKENGINE2018_CORE_H
