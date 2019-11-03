//
// Created by popof on 02.10.2018.
//

#include "GameApplication.h"

#include <Engine.h>
#include <SystemInterface.h>

#include <render/AbstractRenderWindow.h>
#include <performance/PerformanceCounter.h>
#include <util/Screen.h>


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
  auto renderSystem = Engine::GetCurrentRenderSystem();
  auto systemInterface = Engine::GetCurrentSystemInterface();

  try {
    this->logger->info("Creating renderer and render window");

    // Create window
    WindowData data;
    data.title = this->getName();
    data.width = this->getWindowWidth();
    data.height = this->getWindowHeight();
    data.isFullScreen = this->isFullScreen();
    data.contextVersion = {4, 0}; // TODO: choosing or automatic detections

    auto systemWindow = systemInterface->createWindow(data);
    this->window = systemWindow.window;
    this->input = systemWindow.inputSystem;

    this->input->setCursorMode(CursorMode::VISIBLE);
    this->input->setMouseAccelerated(false);

    this->renderer = renderSystem->createRenderer(window);

    Input::Initialize(this->input);
    Screen::Initialize(this->renderer);
  } catch (const Exception &e) {
    throw ApplicationInitializationException(e.getMessage());
  }
}

void GameApplication::stop() {
  this->window->close();
}

}