//
// Created by popof on 02.10.2018.
//

#include "GameApplication.h"

#include <Engine.h>

#include <render/RendererInterface.h>
#include <render/RenderSystemInterface.h>
#include <render/AbstractRenderWindow.h>
#include <performance/PerformanceCounter.h>


namespace black {

GameApplication::GameApplication(const std::string &name, int windowWidth, int windowHeight, bool isFullScreen)
    : AbstractApplication(name, windowWidth, windowHeight, isFullScreen) {
  this->timer = std::make_shared<PerformanceCounter>();
  //this->logger = Logger::Get(name);

  this->setName(std::string("BlackEngine ") + Constants::RuntimePlatformString + " application");
}

void GameApplication::run() {
  this->logger->info("Starting application game loop");

  while (!this->window->shouldClose()) {
    this->timer->update();
    this->update(this->timer->getTimeSinceLastUpdate());
    this->window->updateRenderTarget();
    this->window->pollEvents();
    this->timer->update();
    //this->logger->info("Average FPS: {0}", this->timer->getAverageFps());
  }

  this->logger->info("Finishing application game loop");
}

void GameApplication::init() {
  AbstractApplication::init();

  auto renderSystem = Engine::GetCurrentRenderSystem();
  renderSystem->getSystemInterface()->setCursorMode(CursorMode::VISIBLE);
  renderSystem->getSystemInterface()->setMouseAccelerated(false);

  try {
    this->logger->info("Creating renderer and render window");

    this->renderer = renderSystem->getRenderer();
    this->window = renderSystem->getRenderWindow();
    this->renderer->setCurrentRenderTarget(window);
  } catch (const Exception &e) {
    throw ApplicationInitializationException(e.getMessage());
  }
}

void GameApplication::stop() {
  this->window->close();
}

}