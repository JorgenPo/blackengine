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

        virtual void emitMouseMoved(Window *window, float xOffset, float yOffset) {
            for (const auto &listener : this->listeners) {
                listener->onMouseMoved(window, xOffset, yOffset);
            }
        }

        virtual void emitMouseScrolled(Window *window, double xOffset, double yOffset) {
            for (const auto &listener : this->listeners) {
                listener->onMouseScrolled(window, xOffset, yOffset);
            }
        }

        virtual void emitMouseScrolledDown(Window *window) {
            for (const auto &listener : this->listeners) {
                listener->onMouseScrolledDown(window);
            }
        }

        virtual void emitMouseScrolledUp(Window *window) {
            for (const auto &listener : this->listeners) {
                listener->onMouseScrolledUp(window);
            }
        }
    };

}


#endif //BLACKENGINE_WINDOWEVENTEMITTER_H
