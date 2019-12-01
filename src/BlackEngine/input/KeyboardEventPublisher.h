//
// Created by popov on 30.11.2019.
//

#ifndef BLACKENGINE_KEYBOARDEVENTPUBLISHER_H
#define BLACKENGINE_KEYBOARDEVENTPUBLISHER_H

#include "Keyboard.h"

#include <BlackEngine/common/events/EventPublisher.h>

namespace black {

class KeyboardEventSubscriber;

class KeyboardEventPublisher : private EventPublisher<KeyEvent> {
public:
  void subscribeForKeyboardEvents(std::shared_ptr<KeyboardEventSubscriber> subscriber);

  void publishKeyEvent(const KeyEvent &event);
};

}


#endif //BLACKENGINE_KEYBOARDEVENTPUBLISHER_H
