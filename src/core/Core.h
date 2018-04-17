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
        std::vector<std::shared_ptr<ui::WindowFactory>> factories;
        std::map<std::string, std::shared_ptr<Plugin>> plugins;

        std::unique_ptr<PluginManager> pluginManager;
        Platform platform;
    private:
        Core();

    public:
        static Core& getInstance() {
            static Core instance;
            return instance;
        }

        void addWindowFactory(std::shared_ptr<ui::WindowFactory> factory);
        std::vector<std::shared_ptr<ui::WindowFactory>> getWindowFactories();

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
