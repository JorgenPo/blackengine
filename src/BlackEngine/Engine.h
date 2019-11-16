#ifndef BLACKENGINE_LIBRARY_H
#define BLACKENGINE_LIBRARY_H

#include "common/CommonHeaders.h"
#include "exceptions/Exception.h"

#include <memory>
#include <unordered_map>

namespace black {

class SystemInterface;
class RenderSystemInterface;
class InputSystemInterface;
class PluginManager;
class Logger;
class PluginInterface;
class TerrainBuilder;
class KeyboardEventEmitter;
class MouseEventEmitter;

class BLACK_EXPORTED EngineInitializationException : public Exception {
public:
  explicit EngineInitializationException(const std::string &message);
};

class BLACK_EXPORTED Engine {
private:
  using RenderSystemMap = std::unordered_map<std::string, std::shared_ptr<RenderSystemInterface>>;
  using SystemInterfaceMap = std::unordered_map<std::string, std::shared_ptr<SystemInterface>>;
  using TerrainBuilderMap = std::unordered_map<std::string, std::shared_ptr<TerrainBuilder>>;

  static constexpr const char *GL_RENDERER_PLUGIN_NAME = "glPlugin";
  static constexpr const char *MODEL_PARSERS_PLUGIN_NAME = "modelParsersPlugin";
  static constexpr const char *QT_PLUGIN_NAME = "qtPlugin";

  std::unique_ptr<PluginManager> pluginManager;
  std::shared_ptr<Logger> logger;
  RenderSystemMap renderSystems;
  TerrainBuilderMap terrainBuilders;
  SystemInterfaceMap systemInterfaces;

  std::shared_ptr<RenderSystemInterface> currentRenderSystem;
  std::shared_ptr<SystemInterface> currentSystemInterface;

  std::shared_ptr<KeyboardEventEmitter> keyboard;
  std::shared_ptr<MouseEventEmitter> mouse;

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

  static std::shared_ptr<KeyboardEventEmitter> GetKeyboard() noexcept;
  static std::shared_ptr<MouseEventEmitter> GetMouse() noexcept;

  static TerrainBuilderMap &GetTerrainBuilders();
  static std::shared_ptr<TerrainBuilder> GetTerrainBuilder(std::string_view name);
  static void RegisterTerrainBuilder(std::string_view name, std::shared_ptr<TerrainBuilder> builder);
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
}

#endif