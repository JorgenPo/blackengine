//
// Created by popof on 15.11.2018.
//

#include "Screen.h"

#include <render/AbstractRenderWindow.h>
#include <render/RenderSystemInterface.h>

#include <Engine.h>

namespace black {
float Screen::GetAspectRatio() {
  const auto renderSystem = Engine::GetCurrentRenderSystem();

  if (!renderSystem || !renderSystem->getRenderWindow()) {
    return 0.0f;
  }

  return renderSystem->getRenderWindow()->getRenderTargetAspectRatio();
}

int Screen::GetWidth() {
  const auto renderSystem = Engine::GetCurrentRenderSystem();

  if (!renderSystem || !renderSystem->getRenderWindow()) {
    return 0;
  }

  return renderSystem->getRenderWindow()->getRenderTargetWidth();
}

int Screen::GetHeight() {
  const auto renderSystem = Engine::GetCurrentRenderSystem();

  if (!renderSystem || !renderSystem->getRenderWindow()) {
    return 0;
  }

  return renderSystem->getRenderWindow()->getRenderTargetHeight();
}
}