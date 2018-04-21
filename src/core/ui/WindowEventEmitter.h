//
// Created by popof on 21.04.2018.
//

#ifndef BLACKENGINE_WINDOWEVENTEMITTER_H
#define BLACKENGINE_WINDOWEVENTEMITTER_H

#include "WindowEventListener.h"

#include <memory>
#include <core/events/EventEmitter.h>

namespace black::ui {
    /**
     * Utils methods for window managing
     */
    class WindowEventEmitter : public events::EventEmitter<WindowEventListener> {
    public:
        /**
         * Emits a event when window has been resized
         * @param window    Window pointer
         * @param newWidth  New Window width
         * @param newHeight New Window height
         */
        virtual void emitWindowSizeChanged(Window *window, int newWidth, int newHeight) {
            for (const auto &listener : this->listeners) {
                listener->onWindowSizeChanged(window, newWidth, newHeight);
            }
        }
    };

}


#endif //BLACKENGINE_WINDOWEVENTEMITTER_H
