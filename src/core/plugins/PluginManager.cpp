//
// Created by popof on 26.09.2018.
//
#include "PluginManager.h"

#include "AbstractSharedLibrary.h"
#include "PluginInterface.h"

#include <Types.h>
#include <log/Logger.h>

#include <algorithm>

namespace black {

PluginFunctionNotFound::PluginFunctionNotFound(const std::string &pluginName, const std::string &entryPointName)
    : pluginName(pluginName), entryPointName(entryPointName) {

  this->message << "Plugin '" << pluginName
                << "' does not contain the mandatory function '" << entryPointName << "'";
}

PluginNotFoundException::PluginNotFoundException(
    const std::string &pluginName, const std::vector<std::string> &pluginDirs)
    : pluginName(pluginName), pluginDirs(pluginDirs) {

  this->message << "Plugin with name '" << pluginName << "' not found. Searching dirs are: [";

  for (const auto &dir : pluginDirs) {
    this->message << "\"" << dir << "\", ";
  }

  this->message << "]";
}

PluginManager::PluginManager() {
  /* Default folders */
  this->addPluginDirs({"", "plugins/", fmt::format("{}", config::PLUGIN_PATH)});

  /* Linux */
  if constexpr (Constants::RuntimePlatform == Platform::LINUX) {
    this->addPluginDir("/usr/lib/blackengine/plugins/");
    this->addPluginDir("/usr/lib32/blackengine/plugins/");
    this->addPluginDir("/usr/lib64/blackengine/plugins/");
  }

  this->logger = Logger::Get("PluginManager");
}

void PluginManager::loadPlugin(const std::string& pluginName) {

  this->logger->trace(fmt::format("Loading plugin \"{}\"", pluginName));

  /* Check if plugin was loaded already */
  auto plugin = this->loadedPluginsLibraries.find(pluginName);
  if (plugin != this->loadedPluginsLibraries.end()) {
    this->logger->info(fmt::format("Plugin \"{}\" already loaded", pluginName));
    return;
  }

  auto library = searchForPluginLibrary(pluginName);

  try {
    auto entryPoint = library->getFunction<PluginEntryPoint>(PluginManager::PLUGIN_ENTRY_POINT);

    // Check for exit point also
    library->getFunction<PluginExitPoint>(PluginManager::PLUGIN_EXIT_POINT);

    // Calls the plugin entry point
    entryPoint();

    this->loadedPluginsLibraries[pluginName] = library;
  } catch (const FunctionNotFoundException &e) {
    throw PluginFunctionNotFound(pluginName, e.getFunction());
  }
}

void PluginManager::addPluginDir(const std::string &pluginDir) {
  auto dir = std::find(this->pluginDirs.begin(), this->pluginDirs.end(), pluginDir);
  if (dir != this->pluginDirs.end()) {
    return;
  }

  this->pluginDirs.emplace_back(pluginDir);
}

void PluginManager::addPluginDirs(const std::vector<std::string>& dirs) {
  std::for_each(dirs.begin(), dirs.end(), [&](const auto &dir){ this->addPluginDir(dir); });
}

std::shared_ptr<AbstractSharedLibrary> PluginManager::searchForPluginLibrary(const std::string& pluginName) {
  // Search for plugin in all dirs
  for (auto &pluginDir : this->pluginDirs) {
    this->logger->trace(R"(Looking for "{}" in "{}")", pluginName, pluginDir);

    try {
      auto pluginFullName = pluginDir.empty() ? pluginName : fmt::format("{}/{}", pluginDir, pluginName);
      auto library = std::make_shared<SharedLibrary>(pluginFullName);
      library->load();

      this->logger->info(R"(Plugin "{}" found in "{}")", pluginName, pluginDir);

      // Library found
      return library;
    } catch (const LibraryNotFoundException &e) {
      continue;
    } catch (const Exception &e) {
      this->logger->critical("Exception while loading {0} library: {1}", pluginDir + pluginName, e.getMessage());
      throw Exception(e.getMessage());
    }
  }

  this->logger->error("Failed to load '{0}' plugin", pluginName);

  // Library not found, throw an exception
  throw PluginNotFoundException(pluginName, this->pluginDirs);
}

PluginManager::~PluginManager() = default;

void PluginManager::unloadPlugin(const std::shared_ptr<AbstractSharedLibrary>& plugin) {
  try {
    auto exitPoint = plugin->getFunction<PluginExitPoint>(PLUGIN_EXIT_POINT);
    exitPoint();

    // Free memory
    // #BUG This is causing segfault
    // plugin->unload();
  } catch (const Exception &e) {
    this->logger->critical(e.getMessage());
    return;
  }
}

void PluginManager::initializePlugins() {
  for (const auto &plugin : this->registeredPlugins) {
    plugin.second->initialize();
  }
}

void PluginManager::shutdownPlugins() {
  for (const auto &plugin : this->registeredPlugins) {
    plugin.second->shutdown();
  }
}

void PluginManager::unregisterPlugin(const std::shared_ptr<PluginInterface>& plugin) {
  plugin->uninstall();
  this->registeredPlugins.erase(plugin->getName());
}

void PluginManager::registerPlugin(const std::shared_ptr<PluginInterface>& plugin) {
  this->registeredPlugins[plugin->getName()] = plugin;
  plugin->install();
}

void PluginManager::unloadPlugins() {
  for (const auto &pluginLibrary : this->loadedPluginsLibraries) {
    this->unloadPlugin(pluginLibrary.second);
  }
}

}