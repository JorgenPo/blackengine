#include <utility>

#include <utility>

#include "Engine.h"
#include <thread>

namespace black {

    Engine::Engine() : pluginManager(), renderSystems() {
        this->logger = Logger::Get("Engine");

        logger->trace("Initializing BlackEngine");
        logger->info("Runtime platform is '{0}'", Constants::RuntimePlatformString);

        logger->trace("Initializing Plugin Manager");
        pluginManager = std::make_unique<PluginManager>();
    }

    void Engine::Initialize(std::string title, int width, int height, bool isFullScreen) {
        // Init Logger
        Logger::Initialize();

        if (Constants::IsDebug) {
            Logger::SetLogLevel(LogLevel::TRACE);
        }

        // Main core logger
        Logger::AddLogger(LogTarget::STDOUT, "Engine");

        // Main core error logger
        Logger::AddLogger(LogTarget::STDERR, "EngineErr");

        // Create an instance of engine. Also loads plugins.
        auto engine = Engine::GetInstance();

        engine->setDefaultRenderSystem();

        // Initialize render system
        engine->currentRenderSystem->initialize(std::move(title), width, height, isFullScreen);
    }

    void Engine::UnregisterPlugin(std::shared_ptr<PluginInterface> plugin) {
        plugin->uninstall();
    }

    void Engine::RegisterPlugin(std::shared_ptr<PluginInterface> plugin) {
        auto engine = Engine::GetInstance();
        Engine::GetInstance()->pluginManager->registerPlugin(std::move(plugin));
    }

    void Engine::RegisterRenderSystem(std::shared_ptr<RenderSystemInterface> renderSystem) {
       Engine::GetInstance()->renderSystems["Name"] = std::move(renderSystem);
    }

    Engine::~Engine() {
    }

    void Engine::initializeEngine() {
        logger->trace("Loading core plugins");

        try {
            pluginManager->loadPlugin(GL_RENDERER_PLUGIN_NAME);
        } catch (const PluginNotFoundException &e) {
            Logger::Get("CoreErr")->critical(e.getMessage());
            throw EngineInitializationException(e.getMessage());
        } catch (const PluginFunctionNotFound &e) {
            Logger::Get("CoreErr")->critical(e.getMessage());
            throw EngineInitializationException("GL Plugin corrupted. Exiting");
        }

        // Finally we can initialize all plugins (at this time all
        // plugins were installed and systems loaded)
        pluginManager->initializePlugins();
    }

    void Engine::setDefaultRenderSystem() {
        logger->trace("Set default render system");

        this->currentRenderSystem = this->renderSystems.begin()->second;

        logger->info("Using '{0}' render system as default", this->currentRenderSystem->getName());
    }

    std::shared_ptr<RenderSystemInterface> Engine::GetCurrentRenderSystem() {
        return Engine::GetInstance()->currentRenderSystem;
    }

    void Engine::Shutdown() {
        Engine::GetInstance()->shutdownEngine();
    }

    void Engine::shutdownEngine() {
        logger->trace("Shutdown BlackEngine");

        logger->trace("Shutdown Plugins");

        // Shutdown plugins when all systems are still on boat
        pluginManager->shutdownPlugins();
        pluginManager->unloadPlugins();
    }

    EngineInitializationException::EngineInitializationException(const std::string &message) : Exception(message) {}
}