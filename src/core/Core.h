//
// Created by popof on 15.04.2018.
//

#ifndef BLACKENGINE2018_CORE_H
#define BLACKENGINE2018_CORE_H

#include <memory>
#include <vector>

#include <config/config.h>
#include <core/ui/WindowFactory.h>

#include "PluginManager.h"

namespace black {

    class CoreInitializationException : public Exception {
    public:
        explicit CoreInitializationException(const std::string &message);
    };

    class UnknownPlatformException : public Exception {
    public:
        UnknownPlatformException();
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
    private:
        static Core *instance;

        const std::string CORE_PLUGIN_NAME = "CorePlugin";

        std::vector<std::shared_ptr<ui::WindowFactory>> factories;
        std::map<std::string, std::shared_ptr<Plugin>> plugins;
        std::unique_ptr<PluginManager> pluginManager;
        Platform platform;

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

        void registerWindowFactory(std::shared_ptr<ui::WindowFactory> factory);
        const std::vector<std::shared_ptr<ui::WindowFactory>> &getWindowFactories();

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

    private:
        /**
         * Set up platform information
         */
        void determineTargetPlatform();
    };

}
#endif //BLACKENGINE2018_CORE_H
