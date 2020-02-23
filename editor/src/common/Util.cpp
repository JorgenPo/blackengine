#include "Util.h"

#include <BlackEngine/log/Logger.h>

namespace blackeditor {

std::optional<black::MouseButtonEvent> toBlackengineMouseButtonEvent(QMouseEvent *e) {
  auto button = toBlackengineButton(e->button());
  if (!button.has_value()) {
    black::Logger::Get("FromQtMouseButtonEvent")
        ->warning("Unsupported mouse button event. Mouse button {} pressed.", e->button());
    return {};
  }

  black::MouseButtonAction action = e->type() == QEvent::MouseButtonPress ?
      black::MouseButtonAction::PRESSED : black::MouseButtonAction::RELEASED;

  return black::MouseButtonEvent{
      button.value(),
      action,
      0
  };
}

std::optional<black::MouseButton> toBlackengineButton(Qt::MouseButton button) {
  switch (button) {
  case Qt::MouseButton::LeftButton:return black::MouseButton::LEFT;
  case Qt::MouseButton::RightButton:return black::MouseButton::RIGHT;
  case Qt::MouseButton::MiddleButton:return black::MouseButton::MIDDLE;
  default:return {};
  }
}

}