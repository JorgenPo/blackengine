//
// Created by popof on 15.04.2018.
//
#include "Core.h"
#include <core/os/windows/WindowsSharedLibrary.h>

namespace black {

    Core* Core::instance = nullptr;

    CoreInitializationException::CoreInitializationException(const std::string &message) : Exception(message) {}
    UnknownPlatformException::UnknownPlatformException() : Exception("Unknown target platform") {}

    Core::Core() : platform(Platform::UNKNOWN) {
        // 10 is enough almost for now
        this->factories.reserve(10);

        // Responsible for manage plugins
        this->pluginManager = std::make_unique<PluginManager>();

        determineTargetPlatform();
    }

    void Core::registerWindowFactory(std::shared_ptr<ui::WindowFactory> factory) {
        this->factories.push_back(factory);
    }

    const std::vector<std::shared_ptr<ui::WindowFactory>> &Core::getWindowFactories() {
        return this->factories;
    }

    const std::unique_ptr<PluginManager> &Core::getPluginManager() const {
        return pluginManager;
    }

    std::shared_ptr<SharedLibrary> Core::getPlatformLibrary(std::string name) {
        switch (this->platform) {
            case Platform::WINDOWS:
                return std::make_shared<os::WindowsSharedLibrary>(name);
            case Platform::LINUX:
                // TODO: LINUX
                return std::make_shared<os::WindowsSharedLibrary>(name);
            case Platform::MACOSX:
                // TODO: MACOSX
                return std::make_shared<os::WindowsSharedLibrary>(name);
            default:
                throw UnknownPlatformException();
        }
    }

    Platform Core::getPlatform() const {
        return platform;
    }

    void Core::determineTargetPlatform() {
#ifdef BLACK_PLATFORM_WINDOWS
        this->platform = Platform::WINDOWS;
#elif BLACK_PLATFORM_LINUX
        this->platform = Platform::LINUX;
#elif BLACK_PLATFORM_MACOSX
        this->platform = Platform::MACOSX;
#endif
    }

    void Core::registerPlugin(std::shared_ptr<Plugin> plugin) {
        plugin->install();
    }

    void Core::unregisterPlugin(std::shared_ptr<Plugin> plugin) {
        plugin->uninstall();
    }

    void Core::initialize() {
        // Load core plugin
        try {
            this->pluginManager->loadPlugin(CORE_PLUGIN_NAME);
        } catch(const PluginNotFoundException &e) {
            std::string message = "Failed to load core plugin. Check ";
            message += CORE_PLUGIN_NAME + " shared library exist in application directory";

            throw CoreInitializationException(message);
        }
    }
}
