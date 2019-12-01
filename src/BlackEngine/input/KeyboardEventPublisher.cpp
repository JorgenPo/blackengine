#include "KeyboardEventPublisher.h"
#include "KeyboardEventSubscriber.h"

using namespace black;

void KeyboardEventPublisher::subscribeForKeyboardEvents(std::shared_ptr <KeyboardEventSubscriber> subscriber) {
  this->subscribe(std::move(subscriber));
}

void KeyboardEventPublisher::publishKeyEvent(const KeyEvent &event) {
  EventPublisher<KeyEvent>::publish(event);
}
