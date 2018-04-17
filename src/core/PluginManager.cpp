//
// Created by popof on 17.04.2018.
//
#include "PluginManager.h"
#include "Core.h"

#include <sstream>

namespace black {

    PluginFunctionNotFound::PluginFunctionNotFound(
            const std::string &pluginName, const std::string &entryPointName)
            : pluginName(pluginName), entryPointName(entryPointName) {
        std::stringstream s;

        s << "Plugin '" << pluginName << "' does not contain the mandatory function '"
                                         << entryPointName << "'";
        this->message = s.str();
    }

    PluginNotFoundException::PluginNotFoundException(const std::string &pluginName,
                                                     const std::list<std::string> &pluginDirs) :
            pluginName(pluginName), pluginDirs(pluginDirs) {

        std::stringstream s;
        s << "Plugin with name '" << pluginName << "' not found. Searching paths is: [";

        for (const auto &dir : pluginDirs) {
            s << "\"" << dir << "\"";
        }

        s << "]";

        this->message = s.str();

        // Remove coma after last path
        this->message.erase(this->message.length() - 2, 1);
    }

    PluginManager::PluginManager()
    {
        /* Plugins must be placed to dll folder by default */
        this->pluginDirs.emplace_back("");
    }

    PluginManager::PluginManager(std::string configFile) {

    }

    void PluginManager::loadPlugins(std::string configFile) {

    }

    void PluginManager::loadPlugin(std::string pluginName) {
        /* Check if plugin was loaded already */
        auto plugin = this->loadedPlugins.find(pluginName);
        if (plugin != this->loadedPlugins.end()) {
            return;
        }

        auto library = searchForPluginLibrary(pluginName);

        try {
            auto entryPoint = reinterpret_cast<PluginEntryPoint>(
                    library->getFunction(PluginManager::PLUGIN_ENTRY_POINT));

            // Check for exit point also
            auto exitPoint = reinterpret_cast<PluginExitPoint>(
                    library->getFunction(PluginManager::PLUGIN_EXIT_POINT));

            // Calls the plugin entry point
            entryPoint();

            this->loadedPlugins[pluginName] = library;
        } catch (const FunctionNotFoundException &e) {
            throw PluginFunctionNotFound(pluginName, e.getFunction());
        }
    }

    void PluginManager::addPluginDir(std::string pluginDir) {

    }

    void PluginManager::addPluginDirs(std::list<std::string> pluginDirs) {

    }

    void PluginManager::parseConfig(std::ifstream file) {

    }

    std::shared_ptr<SharedLibrary> PluginManager::searchForPluginLibrary(std::string pluginName) {
        auto core = Core::getInstance();

        // Search for plugin in all dirs
        for (auto &pluginDir : this->pluginDirs) {
            try {
                auto library = core->getPlatformLibrary(pluginDir + pluginName);
                library->load();

                // Library found
                return library;
            } catch (const LibraryNotFoundException &e) {
                continue;
            }
        }

        // Library not found, throw an exception
        throw PluginNotFoundException(pluginName, this->pluginDirs);
    }

    PluginManager::~PluginManager() {
        for (const auto &plugin : this->loadedPlugins) {
            unloadPlugin(plugin.second);
        }
    }

    void PluginManager::unloadPlugin(std::shared_ptr<SharedLibrary> plugin) {
        try {
            auto exitPoint = reinterpret_cast<PluginExitPoint>(plugin->getFunction(PLUGIN_EXIT_POINT));

            exitPoint();
        } catch(...) {
            return;
        }
    }

}