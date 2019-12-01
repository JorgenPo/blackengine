//
// Created by popov on 31.07.2019.
//

#ifndef BLACKENGINE_MOUSEEVENTSUBSCRIBER_H
#define BLACKENGINE_MOUSEEVENTSUBSCRIBER_H

#include "Mouse.h"

#include <BlackEngine/common/events/EventSubscriber.h>

namespace black {

class MouseEventSubscriber :
  public EventSubscriber<MouseButtonEvent>,
  public EventSubscriber<MouseMovedEvent> {
public:
  virtual void onMouseButtonEvent(const MouseButtonEvent &event) = 0;
  virtual void onMouseButtonPressed(const MouseButtonEvent &event) = 0;
  virtual void onMouseButtonReleased(const MouseButtonEvent &event) = 0;
  virtual void onMouseMoved(const MouseMovedEvent &event) = 0;

private:
  void onEvent(const MouseButtonEvent &event) override {
    onMouseButtonEvent(event);

    switch (event.action) {
      case MouseButtonAction::PRESSED:
        onMouseButtonPressed(event);
        break;
      case MouseButtonAction::RELEASED:
        onMouseButtonReleased(event);
        break;
    }
  }

  void onEvent(const MouseMovedEvent &event) override {
    onMouseMoved(event);
  }
};

}


#endif //BLACKENGINE_MOUSEEVENTSUBSCRIBER_H
