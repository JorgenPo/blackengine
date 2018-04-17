//
// Created by popof on 17.04.2018.
//

#ifndef BLACKENGINE_PLUGINMANAGER_H
#define BLACKENGINE_PLUGINMANAGER_H


#include <map>
#include <string>
#include <memory>
#include <list>
#include <fstream>
#include "Plugin.h"
#include "Exception.h"
#include "SharedLibrary.h"

namespace black {

    class PluginNotFoundException : public Exception {
        std::string pluginName;
        std::list<std::string> pluginDirs;

    public:
        PluginNotFoundException(const std::string &pluginName, const std::list<std::string> &pluginDirs);

    };

    class PluginFunctionNotFound : public Exception {
        std::string pluginName;
        std::string entryPointName;

    public:
        PluginFunctionNotFound(const std::string &pluginName, const std::string &entryPointName);
    };

    /**
     * Manages plugin loading
     */
    class PluginManager {
        const std::string PLUGIN_ENTRY_POINT = "BlackPluginInstall";
        const std::string PLUGIN_EXIT_POINT = "BlackPluginUninstall";

        std::map<std::string, std::shared_ptr<SharedLibrary>> loadedPlugins;
        std::list<std::string> pluginDirs;

        typedef void (*PluginEntryPoint)();
        typedef void (*PluginExitPoint)();
    public:
        /**
         * Initialize an empty plugin manager.
         * You can manually load plugin via loadPlugin() function
         */
        PluginManager();
        ~PluginManager();

        /**
         * Initialize plugin manager with provided
         * config file name in ini format, config file
         * may contain plugin names to be loaded
         *
         * @param configFile Config filename
         */
        explicit PluginManager(std::string configFile);

        /**
         * Load all plugins listed in configFile
         *
         * @param configFile Config file
         */
        void loadPlugins(std::string configFile);

        /**
         * Load a plugin by name. PluginManager looking for
         * a plugin in all pluginDirectories, appending extension to
         * its name (.dll for windows, .so for linux and so on...)
         *
         * @throws PluginNotFoundException if plugin not found in all
         * search dirs
         *
         * @throws PluginEntryPointNotFoundException if plugin does not contains
         * an entry point
         *
         * @param pluginName Plugin name.
         */
        void loadPlugin(std::string pluginName);

        /**
         * Add directory to search for plugins while loading
         *
         * @param pluginDir Directory name
         */
        void addPluginDir(std::string pluginDir);

        /**
         * Add directories to search for plugins while loading
         * @param pluginDirs
         */
        void addPluginDirs(std::list<std::string> pluginDirs);

    private:
        /**
         * Parse config
         *
         * @param file Input stream to config file
         */
        void parseConfig(std::ifstream file);

        /**
         * Search for plugin in all plugin directories
         *
         * @throws PluginNotFoundException if plugin not found in all
         * search dirs
         * @param pluginName Plugin name without extension
         */
        std::shared_ptr<SharedLibrary> searchForPluginLibrary(std::string pluginName);

        /**
         * Unloads a plugin. Calls PLUGIN_EXIT_POINT function in dll
         *
         * @param plugin Plugin to unload
         */
        void unloadPlugin(std::shared_ptr<SharedLibrary> plugin);
    };

}


#endif //BLACKENGINE_PLUGINMANAGER_H
