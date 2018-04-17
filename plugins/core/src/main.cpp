
#include <memory>

#include "CorePlugin.h"
#include <core/Core.h>

std::shared_ptr<black::CorePlugin> plugin;

extern "C" void BlackPluginInstall() {
    plugin = std::make_shared<black::CorePlugin>();

    auto core = black::Core::getInstance();
    core->registerPlugin(plugin);
}

extern "C" void BlackPluginUninstall() {
    auto core = black::Core::getInstance();
    core->unregisterPlugin(plugin);

    plugin.reset();
}