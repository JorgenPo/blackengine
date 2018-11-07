#include <Engine.h>
#include <iostream>

#include "ModelParsersPlugin.h"

std::shared_ptr<black::ModelParsersPlugin> plugin;

extern "C" void BlackPluginInstall() {
    plugin = std::make_shared<black::ModelParsersPlugin>();

    black::Engine::RegisterPlugin(plugin);
}

extern "C" void BlackPluginUninstall() {
    black::Engine::UnregisterPlugin(plugin);
}