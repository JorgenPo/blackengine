//
// Created by popov on 30.11.2019.
//

#ifndef BLACKENGINEEVENTS__EVENTPUBLISHER_H
#define BLACKENGINEEVENTS__EVENTPUBLISHER_H

#include "EventSubscriber.h"

#include <vector>
#include <memory>

namespace black {

template<typename EventType>
class EventPublisher {
  using SubscriberWeak = std::weak_ptr<EventSubscriber<EventType>>;
  using Subscriber = std::shared_ptr<EventSubscriber<EventType>>;

  std::vector<SubscriberWeak> subscribers;

protected:
  void publish(const EventType &event) {
    for (auto &&weakSubscriber : subscribers) {
      if (auto subscriber = weakSubscriber.lock(); subscriber) {
        subscriber->onEvent(event);
      }
    }
  }

  template<typename ...EventArgs>
  void publish(EventArgs ...args) {
    for (auto &&weakSubscriber : subscribers) {
      if (auto subscriber = weakSubscriber.lock(); subscriber) {
        subscriber->onEvent(EventType{std::forward<EventArgs>(args)...});
      }
    }
  }

public:
  void subscribe(Subscriber subscriber) {
    subscribers.push_back(std::move(subscriber));
  }
};

}

#endif //BLACKENGINEEVENTS__EVENTPUBLISHER_H
