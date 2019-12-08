#include "Engine.h"
#include "common/Config.h"
#include "SystemInterface.h"

#include "log/Logger.h"
#include "plugins/PluginInterface.h"
#include "plugins/PluginManager.h"
#include "render/RenderSystemInterface.h"
#include "terrain/FlatTerrainBuilder.h"
#include "camera/CameraFactory.h"
#include "camera/RTSCamera.h"

#include <memory>

namespace black {

Engine::Engine() :
pluginManager(),
renderSystems() {

  this->logger = Logger::Get("Engine");

  logger->trace("Initializing BlackEngine v{}", config::VERSION_STRING);
  logger->info("Runtime platform is '{0}'", Constants::RuntimePlatformString);

  logger->trace("Initializing Plugin Manager");
  pluginManager = std::make_unique<PluginManager>();
}

void Engine::Initialize() {
  // Init Logger
  Logger::Initialize();

  if constexpr (Constants::IsDebug) {
    Logger::SetLogLevel(LogLevel::TRACE);
  }

  try {
    // Main core logger
    Logger::AddLogger(LogTarget::STDOUT, "Engine");

    // Main core error logger
    Logger::AddLogger(LogTarget::STDERR, "EngineErr");
  } catch (const std::exception &e) {
    // Just ignore
  }
  Logger::Get("Engine")->info("Logger initialized");

  // Create an instance of engine. Also loads plugins.
  auto engine = Engine::GetInstance();

  // System interface should be created before the renderer
  engine->setDefaultSystemInterface();
  engine->setDefaultRenderSystem();

  // Initialize render system
  engine->currentRenderSystem->initialize();

  RegisterTerrainBuilder(FlatTerrainBuilder::GetName(), std::make_shared<FlatTerrainBuilder>());
  RegisterCameraFactory(RTSCamera::Factory::GetName(), std::make_shared<RTSCamera::Factory>());
}

void Engine::UnregisterPlugin(const std::shared_ptr<PluginInterface>& plugin) {
  plugin->uninstall();
}

void Engine::RegisterPlugin(const std::shared_ptr<PluginInterface>& plugin) {
  auto engine = Engine::GetInstance();
  Engine::GetInstance()->pluginManager->registerPlugin(plugin);
  Logger::Get("Engine")->info("Plugin with name '{0}' registered", plugin->getName());
}

void Engine::RegisterRenderSystem(std::shared_ptr<RenderSystemInterface> renderSystem) {
  if (!renderSystem) {
    return;
  }

  auto name = renderSystem->getName();
  Engine::GetInstance()->renderSystems[name] = std::move(renderSystem);
  Logger::Get("Engine")->info("Render system '{0}' registered", name);
}

Engine::~Engine() = default;

void Engine::initializeEngine() {
  SetTerminationHandler();

  logger->trace("Loading core plugins");

  try {
    pluginManager->loadPlugin(GL_RENDERER_PLUGIN_NAME);
    pluginManager->loadPlugin(MODEL_PARSERS_PLUGIN_NAME);
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
  logger->trace("Setting default render system");

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

void Engine::SetTerminationHandler() {
  std::set_terminate([]() {
    std::string message("Undefined exception");

    if (auto lastException = std::current_exception()) {
      try {
        std::rethrow_exception(lastException);
      } catch (const Exception &e) {
        message = e.getMessage();
      } catch (const std::exception &e) {
        message = e.what();
      }

      Logger::Get("Engine")->critical("Program terminated after throwing an exception:\n\t{0}", message);
    }

    std::abort();
  });
}

Engine::TerrainBuilderMap &Engine::GetTerrainBuilders() {
  return GetInstance()->terrainBuilders;
}

std::shared_ptr<TerrainBuilder> Engine::GetTerrainBuilder(std::string_view name) {
  try {
    return GetTerrainBuilders().at(name.data());
  } catch (const std::exception &e) {
    throw NotFoundException(fmt::format("TerrainBuilder '{}' not found", name));
  }
}

void Engine::RegisterTerrainBuilder(std::string_view name, std::shared_ptr<TerrainBuilder> builder) {
  if (!builder) {
    return;
  }

  GetInstance()->terrainBuilders[name.data()] = std::move(builder);
  Logger::Get("Engine")->info("Terrain builder '{0}' registered", name);
}

void Engine::RegisterSystemInterface(std::shared_ptr<SystemInterface> systemInterface) {
  if (!systemInterface) {
    return;
  }

  auto name = systemInterface->getName();
  GetInstance()->systemInterfaces[systemInterface->getName()] = std::move(systemInterface);
  Logger::Get("Engine")->info("System interface '{0}' registered", name);
}

std::shared_ptr<SystemInterface> Engine::GetCurrentSystemInterface() {
  return Engine::GetInstance()->currentSystemInterface;
}

void Engine::setDefaultSystemInterface() {
  logger->trace("Setting default system interface");

  this->currentSystemInterface = this->systemInterfaces.begin()->second;

  logger->info("Using '{0}' system interface as default", this->currentSystemInterface->getName());
}

void Engine::RegisterCameraFactory(std::string_view name, std::shared_ptr<CameraFactory> factory) {
  Logger::Get("Engine")->info("Registering camera factory '{}'", name);
  Engine::GetInstance()->cameraFactories[name.data()] = std::move(factory);
}

EngineInitializationException::EngineInitializationException(const std::string &message) : Exception(message) {}
}