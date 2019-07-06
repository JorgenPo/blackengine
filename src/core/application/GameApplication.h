//
// Created by popof on 02.10.2018.
//

#ifndef BLACKENGINE_GAMEAPPLICATION_H
#define BLACKENGINE_GAMEAPPLICATION_H

#include "AbstractApplication.h"

#include <CommonHeaders.h>

#include <Engine.h>
#include <Image.h>
#include <GameEntity.h>
#include <Camera.h>

#include <render/AbstractRenderWindow.h>
#include <render/RenderSystemInterface.h>
#include <render/RendererInterface.h>
#include <render/Material.h>

#include <components/ModelComponent.h>
#include <components/TransformComponent.h>
#include <components/LightComponent.h>

#include <performance/PerformanceCounter.h>

#include <util/ModelManager.h>
#include <util/Input.h>

namespace black {

/**
 * Single window and real time updating application.
 */
class BLACK_EXPORTED GameApplication : public AbstractApplication {
protected:
  std::shared_ptr<AbstractRenderWindow> window;
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
