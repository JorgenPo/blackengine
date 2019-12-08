//
// Created by popov on 30.11.2019.
//

#include "MouseEventPublisher.h"
#include "MouseEventSubscriber.h"

using namespace black;

void MouseEventPublisher::subscribeForMouseEvents(std::shared_ptr<MouseEventSubscriber> subscriber) {
  EventPublisher<MouseButtonEvent>::subscribe(std::move(subscriber));
  EventPublisher<MouseMovedEvent>::subscribe(std::move(subscriber));
}

void MouseEventPublisher::publishMouseButtonEvent(const MouseButtonEvent &event) {
  EventPublisher<MouseButtonEvent>::publish(event);
}

void MouseEventPublisher::publishMouseMovedEvent(const MouseMovedEvent &event) {
  EventPublisher<MouseMovedEvent>::publish(event);
}

void MouseEventPublisher::publishScrollEvent(const ScrollEvent &event) {
  EventPublisher<ScrollEvent>::publish(event);
}
