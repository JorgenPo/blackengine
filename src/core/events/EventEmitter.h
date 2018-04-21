//
// Created by popof on 21.04.2018.
//

#ifndef BLACKENGINE_EVENTEMMITER_H
#define BLACKENGINE_EVENTEMMITER_H

#include <memory>
#include <list>
#include "EventListener.h"

namespace black::events {
    /**
     * Interface for a class capable to emit
     * some events
     */
    template <typename EventListenerClass>
    class EventEmitter {
    protected:
        std::list<std::shared_ptr<EventListenerClass>> listeners;

    public:
        void listen(const std::shared_ptr<EventListenerClass> &listener) {
            listeners.push_back(listener);
        }

        void stopListen(const std::shared_ptr<EventListenerClass> &listener) {
            listeners.remove(listener);
        }
    };
}


#endif //BLACKENGINE_EVENTEMMITER_H
