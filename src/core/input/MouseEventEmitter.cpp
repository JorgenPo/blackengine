//
// Created by popov on 31.07.2019.
//

#include "MouseEventEmitter.h"
#include "MouseEventListener.h"

namespace black {

void MouseEventEmitter::listenForMouseEvents(MouseEventListener *listener) {
  listeners.push_back(listener);
}

void MouseEventEmitter::emitMouseButtonEvent(MouseButtonEvent event) {
  for (auto && listener : listeners) {
    listener->onMouseButtonEvent(event);

    if (event.action == MouseButtonAction::PRESSED) {
      listener->onMouseButtonPressed(event);
    } else {
      listener->onMouseButtonReleased(event);
    }
  }
}

}