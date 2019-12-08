#ifndef BLACKENGINE_MOUSEEVENTPUBLISHER_H
#define BLACKENGINE_MOUSEEVENTPUBLISHER_H

#include "Mouse.h"

#include <BlackEngine/common/events/EventPublisher.h>

namespace black {

class MouseEventSubscriber;

class MouseEventPublisher :
  private EventPublisher<MouseButtonEvent>,
  private EventPublisher<MouseMovedEvent>,
  private EventPublisher<ScrollEvent> {

public:
  void subscribeForMouseEvents(std::shared_ptr<MouseEventSubscriber> subscriber);

  void publishMouseButtonEvent(const MouseButtonEvent &event);
  void publishMouseMovedEvent(const MouseMovedEvent &event);
  void publishScrollEvent(const ScrollEvent &event);
};

}


#endif //BLACKENGINE_MOUSEEVENTPUBLISHER_H
