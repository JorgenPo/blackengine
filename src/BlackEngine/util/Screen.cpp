//
// Created by popof on 15.11.2018.
//

#include "Screen.h"

#include <BlackEngine/render/AbstractRenderWindow.h>
#include <BlackEngine/render/RenderSystemInterface.h>

#include "../Engine.h"

#include <BlackEngine/render/RendererInterface.h>

namespace black {

std::shared_ptr<RendererInterface> Screen::renderer;

float Screen::GetAspectRatio() {
  if (!renderer) {
    throw FatalError("Screen helper class is unitialized: render is nullptr!");
  }

  return renderer->getCurrentRenderTarget()->getRenderTargetAspectRatio();
}

int Screen::GetWidth() {
  if (!renderer) {
    throw FatalError("Screen helper class is unitialized: render is nullptr!");
  }

  return static_cast<int>(renderer->getCurrentRenderTarget()->getRenderTargetWidth());
}

int Screen::GetHeight() {
  const auto renderSystem = Engine::GetCurrentRenderSystem();

  if (!renderer) {
    throw FatalError("Screen helper class is unitialized: render is nullptr!");
  }

  return static_cast<int>(renderer->getCurrentRenderTarget()->getRenderTargetHeight());
}

void Screen::Initialize(std::shared_ptr<RendererInterface> newRenderer) noexcept {
  renderer = std::move(newRenderer);
}
}