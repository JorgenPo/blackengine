//
// Created by popov on 30.11.2019.
//

#ifndef BLACKENGINEEVENTS__EVENTSUBSCRIBER_H
#define BLACKENGINEEVENTS__EVENTSUBSCRIBER_H

namespace black {

template<typename EventType>
class EventSubscriber {
public:
  virtual void onEvent(const EventType &event) = 0;
};

}

#endif //BLACKENGINEEVENTS__EVENTSUBSCRIBER_H
