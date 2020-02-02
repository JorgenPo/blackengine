#ifndef BLACKENGINE_LIBRARY_H
#define BLACKENGINE_LIBRARY_H

#include "common/CommonHeaders.h"
#include "exceptions/Exception.h"

#include <BlackEngine/render/RenderTargetInterface.h>
#include <BlackEngine/camera/Camera.h>

#include <memory>
#include <unordered_map>

#include <glm/glm.hpp>

namespace black {

class SystemInterface;
class RenderSystemInterface;
class InputSystemInterface;
class PluginManager;
class Logger;
class PluginInterface;
class TerrainBuilder;
class CameraFactory;

class BLACK_EXPORTED EngineInitializationException : public Exception {
public:
  explicit EngineInitializationException(const std::string &message);
};

class BLACK_EXPORTED Engine {
private:
  using RenderSystemMap = std::unordered_map<std::string, std::shared_ptr<RenderSystemInterface>>;
  using SystemInterfaceMap = std::unordered_map<std::string, std::shared_ptr<SystemInterface>>;
  using TerrainBuilderMap = std::unordered_map<std::string, std::shared_ptr<TerrainBuilder>>;
  using CameraFactoryMap = std::unordered_map<std::string, std::shared_ptr<CameraFactory>>;

  static constexpr const char *GL_RENDERER_PLUGIN_NAME = "glPlugin";
  static constexpr const char *MODEL_PARSERS_PLUGIN_NAME = "modelParsersPlugin";
  static constexpr const char *QT_PLUGIN_NAME = "qtPlugin";

  std::unique_ptr<PluginManager> pluginManager;
  std::shared_ptr<Logger> logger;
  RenderSystemMap renderSystems;
  TerrainBuilderMap terrainBuilders;
  SystemInterfaceMap systemInterfaces;
  CameraFactoryMap cameraFactories;

  std::shared_ptr<RenderSystemInterface> currentRenderSystem;
  std::shared_ptr<SystemInterface> currentSystemInterface;

  /**
   * This method is private. Use appropriate static methods.
   *
   * @return Engine instance.
   */
  static std::shared_ptr<Engine> GetInstance() {
    static std::shared_ptr<Engine> engine;

    if (!engine) {
      engine = std::shared_ptr<Engine>(new Engine());
      engine->initializeEngine();
    }

    return engine;
  }

  Engine();
public:
  ~Engine();

  /**
   * Initialize an Engine. Must be called before any usage of Engine.
   * Main render window parameters passed as arguments
   *
   * @throws EngineInitializationException
   */
  static void Initialize();

  /**
   * Must be called explicitly to shutdown all engine's systems.
   */
  static void Shutdown();

  /**
   * Register external plugin. Must be invoked in plugin entry point
   *
   * @param plugin Plugin to be registered
   */
  static void RegisterPlugin(const std::shared_ptr<PluginInterface>& plugin);

  /**
   * Unregister external plugin
   *
   * @param plugin Plugin to be unregistered. Must be invoked in plugin exit point
   */
  static void UnregisterPlugin(const std::shared_ptr<PluginInterface>& plugin);

  /**
   * Register a new render system. Render system will be available by it's name.
   */
  static void RegisterRenderSystem(std::shared_ptr<RenderSystemInterface> renderSystem);

  /**
   * Register new system interface class. System interface interacts with Operating System.
   * And provides user input handling.
   *
   * @param systemInterface
   */
  static void RegisterSystemInterface(std::shared_ptr<SystemInterface> systemInterface);

  /**
   * Return a currently active render system
   */
  static std::shared_ptr<RenderSystemInterface> GetCurrentRenderSystem();

  static std::shared_ptr<SystemInterface> GetCurrentSystemInterface();

  static TerrainBuilderMap &GetTerrainBuilders();
  static std::shared_ptr<TerrainBuilder> GetTerrainBuilder(std::string_view name);
  static void RegisterTerrainBuilder(std::string_view name, std::shared_ptr<TerrainBuilder> builder);

  // Camera functions
  static void RegisterCameraFactory(std::string_view name, std::shared_ptr<CameraFactory> factory);

  /**
   * Create a camera. CameraType type should have inner public class Factory representing
   * camera factory. Factory inner class should have GetName static method returning
   * a string with the name of the Camera class created by the Factory.
   *
   * @param data Data to create the camera from
   * @return Camera created in the factory
   *
   * @throws FactoryNotFoundException If a factory with the given name not found
   */
  template<typename CameraType>
  static std::shared_ptr<CameraType> CreateCamera(const CameraData &data);
private:
  /**
   * Initialize engine. Load plugins.
   *
   * @return
   */
  void initializeEngine();

  /**
   * Called from Shutdown static method.
   */
  void shutdownEngine();

  /**
   * Set a default render system. Just took first available.
   */
  void setDefaultRenderSystem();

  void setDefaultSystemInterface();

  static void SetTerminationHandler();
};

template<typename CameraType>
std::shared_ptr<CameraType> Engine::CreateCamera(const CameraData &data) {
  auto name = CameraType::Factory::GetName();

  try {
    return std::dynamic_pointer_cast<CameraType>(
      Engine::GetInstance()->cameraFactories.at(name)->create(data));
  } catch (const std::out_of_range &e) {
    throw FactoryNotFoundException(name);
  }
}

}

#endif