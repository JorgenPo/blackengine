#ifndef BLACKENGINE_MOUSEEVENTPUBLISHER_H
#define BLACKENGINE_MOUSEEVENTPUBLISHER_H

#include "Mouse.h"

#include <BlackEngine/common/events/EventPublisher.h>

namespace black {

class MouseEventSubscriber;

class MouseEventPublisher :
  private EventPublisher<MouseButtonEvent>,
  private EventPublisher<MouseMovedEvent> {

public:
  void subscribeForMouseButtonEvent(std::shared_ptr<MouseEventSubscriber> subscriber);

  void publishMouseButtonEvent(const MouseButtonEvent &event);
  void publishMouseMovedEvent(const MouseMovedEvent &event);
};

}


#endif //BLACKENGINE_MOUSEEVENTPUBLISHER_H
