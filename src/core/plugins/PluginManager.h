//
// Created by popof on 26.09.2018.
//

#ifndef BLACKENGINE_PLUGINMANAGER_H
#define BLACKENGINE_PLUGINMANAGER_H

#include <CommonHeaders.h>
#include <exceptions/Exception.h>

#include <list>
#include <map>

namespace black {

class Logger;
class PluginInterface;
class AbstractSharedLibrary;

/**
 * Plugin has not been found
 */
class BLACK_EXPORTED PluginNotFoundException : public Exception {
  std::string pluginName;
  std::list<std::string> pluginDirs;

public:
  /**
   * Constructor
   *
   * @param pluginName Name of a plugin
   * @param pluginDirs Directories in which plugins are searched
   */
  PluginNotFoundException(const std::string &pluginName, const std::list<std::string> &pluginDirs);
};

class BLACK_EXPORTED PluginFunctionNotFound : public Exception {
  std::string pluginName;
  std::string entryPointName;

public:
  PluginFunctionNotFound(const std::string &pluginName, const std::string &entryPointName);
};

/**
 * Manages plugin lifecycle. Loading and unloading.
 * Contains all loaded plugins.
 */
class BLACK_EXPORTED PluginManager {
  using PluginsLibriesMap = std::map<std::string, std::shared_ptr<AbstractSharedLibrary>>;
  using PluginsMap = std::map<std::string, std::shared_ptr<PluginInterface>>;

  const std::string PLUGIN_ENTRY_POINT = "BlackPluginInstall";
  const std::string PLUGIN_EXIT_POINT = "BlackPluginUninstall";

  PluginsLibriesMap loadedPluginsLibraries;
  PluginsMap registeredPlugins;

  std::list<std::string> pluginDirs;

  typedef void (*PluginEntryPoint)();
  typedef void (*PluginExitPoint)();

  std::shared_ptr<Logger> logger;
public:
  /**
   * Initialize an empty plugin manager.
   * You can manually load plugin via loadPlugin() function
   */
  PluginManager();
  ~PluginManager();

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
  void addPluginDir(const std::string &pluginDir);

  /**
   * Add directories to search for plugins while loading
   * @param pluginDirs
   */
  void addPluginDirs(std::list<std::string> pluginDirs);

  /**
   * Add plugin object as registered plugin.
   * Calls an install method of a plugin.
   */
  void registerPlugin(std::shared_ptr<PluginInterface> plugin);

  /**
   * Remove plugin from registered plugins list.
   * Calls an uninstall method of a plugin.
   */
  void unregisterPlugin(std::shared_ptr<PluginInterface> plugin);

  /**
   * Calls initialize of all plugins loaded at a time of call
   */
  void initializePlugins();

  /**
   * Call shutdown of all plugins loaded at a time of call
   */
  void shutdownPlugins();

  /**
   * Called just before plugin manager destruction by core object.
   * Plugin should finally reset all objects. At this time no other systems or
   * plugins should be considered as living.
   *
   */
  void unloadPlugins();
private:
  /**
   * Search for plugin in all plugin directories
   *
   * @throws PluginNotFoundException if plugin not found in all
   * search dirs
   * @param pluginName Plugin name without extension
   */
  std::shared_ptr<AbstractSharedLibrary> searchForPluginLibrary(std::string pluginName);

  /**
   * Unloads a plugin. Calls PLUGIN_EXIT_POINT function in dll
   *
   * @param plugin Plugin to unload
   */
  void unloadPlugin(std::shared_ptr<AbstractSharedLibrary> plugin);
};

}

#endif //BLACKENGINE_PLUGINMANAGER_H
