//
// Created by popof on 21.04.2018.
//

#ifndef BLACKENGINE_WINDOWEVENTLISTENER_H
#define BLACKENGINE_WINDOWEVENTLISTENER_H

#include <core/events/EventListener.h>
#include <memory>

namespace black::ui {
    class Window;

    /**
     * Class that want to listen window
     * events.
     */
    class WindowEventListener : public events::EventListener {
    public:
        virtual void onWindowSizeChanged(Window *window, int newWidth, int newHeight) {}
    };
}


#endif //BLACKENGINE_WINDOWEVENTLISTENER_H
