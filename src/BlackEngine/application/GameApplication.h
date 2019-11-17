//
// Created by popof on 02.10.2018.
//

#ifndef BLACKENGINE_GAMEAPPLICATION_H
#define BLACKENGINE_GAMEAPPLICATION_H

#include "AbstractApplication.h"

#include "../common/CommonHeaders.h"

#include "../Engine.h"
#include "../Image.h"
#include "../GameObject.h"
#include "../Camera.h"

#include <BlackEngine/render/AbstractRenderWindow.h>
#include <BlackEngine/render/RenderSystemInterface.h>
#include <BlackEngine/render/RendererInterface.h>
#include <BlackEngine/render/Material.h>

#include <BlackEngine/shader/ApplicationShader.h>
#include <BlackEngine/log/Formatters.h>
#include <BlackEngine/scene/SimpleScene.h>

#include "BlackEngine/components/ModelComponent.h"
#include "BlackEngine/components/TransformComponent.h"
#include "BlackEngine/components/LightComponent.h"
#include "BlackEngine/components/TerrainComponent.h"
#include "BlackEngine/components/BoundingComponent.h"

#include <BlackEngine/performance/PerformanceCounter.h>

#include <BlackEngine/util/ModelManager.h>
#include <BlackEngine/util/Input.h>
#include <BlackEngine/util/ShaderManager.h>

namespace black {

/**
 * Single window and real time updating application.
 */
class BLACK_EXPORTED GameApplication : public AbstractApplication {
protected:
  std::shared_ptr<AbstractRenderWindow> window;
  std::shared_ptr<InputSystemInterface> input;
  std::shared_ptr<RendererInterface> renderer;
  std::shared_ptr<PerformanceCounter> timer;

public:
  /**
   * Init application with a given name and a game window properties
   *
   * @param name              Name of the application
   * @param windowWidth       Application window width
   * @param windowHeight      Application window height
   * @param isFullScreen      Is the application window should be shown as fullscreen
   *
   * @throws ApplicationInitializationException If failed to init a window
   */
  explicit GameApplication(const std::string &name, int windowWidth, int windowHeight, bool isFullScreen);
private:
  void run() override;

protected:
  void init() override;
  void stop();
};
}

#endif //BLACKENGINE_GAMEAPPLICATION_H
