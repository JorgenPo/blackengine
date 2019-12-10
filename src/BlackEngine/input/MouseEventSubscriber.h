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
  public EventSubscriber<MouseMovedEvent>,
  public EventSubscriber<ScrollEvent> {
public:
  virtual void onMouseButtonEvent(const MouseButtonEvent &event) {}
  virtual void onMouseButtonPressed(const MouseButtonEvent &event) {}
  virtual void onMouseButtonReleased(const MouseButtonEvent &event) {}
  virtual void onMouseMoved(const MouseMovedEvent &event) {}
  virtual void onScroll(float offsetX, float offsetY) {}
  virtual void onScrollY(float dY) {}
  virtual void onScrollX(float dX) {}

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

  void onEvent(const ScrollEvent &event) override {
    onScroll(event.offsetX, event.offsetY);
    onScrollX(event.offsetX);
    onScrollY(event.offsetY);
  }
};

}


#endif //BLACKENGINE_MOUSEEVENTSUBSCRIBER_H
