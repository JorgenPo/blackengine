#include <BlackEngine/Engine.h>
#include <iostream>

#include "GLPlugin.h"

std::shared_ptr<black::GLPlugin> plugin;

extern "C" void BlackPluginInstall() {
  plugin = std::make_shared<black::GLPlugin>();

  black::Engine::RegisterPlugin(plugin);
}

extern "C" void BlackPluginUninstall() {
  black::Engine::UnregisterPlugin(plugin);
}