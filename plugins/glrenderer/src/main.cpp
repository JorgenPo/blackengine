
#include <memory>

#include "GLRendererPlugin.h"
#include <core/Core.h>

std::shared_ptr<black::GLRendererPlugin> plugin;

extern "C" void BlackPluginInstall() {
    plugin = std::make_shared<black::GLRendererPlugin>();

    auto core = black::Core::getInstance();
    core->registerPlugin(plugin);
}

extern "C" void BlackPluginUninstall() {
    auto core = black::Core::getInstance();
    core->unregisterPlugin(plugin);
    plugin.reset();
}