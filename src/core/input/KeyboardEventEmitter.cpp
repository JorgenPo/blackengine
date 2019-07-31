//
// Created by popov on 31.07.2019.
//

#include "KeyboardEventEmitter.h"
#include "KeyboardEventListener.h"

namespace black {

void KeyboardEventEmitter::listenForKeyboardEvents(KeyboardEventListener *listener) {
  listeners.push_back(listener);
}

void KeyboardEventEmitter::emitKeyPressedEvent(KeyEvent keyEvent) {
  for (auto && listener : listeners) {
    listener->onKeyEvent(keyEvent);

    switch (keyEvent.action) {
      case KeyAction::PRESSED:
        listener->onKeyPressed(keyEvent);
        break;
      case KeyAction::RELEASED:
        listener->onKeyReleased(keyEvent);
        break;
      case KeyAction::REPEAT:
        listener->onKeyRepeat(keyEvent);
        break;
    }
  }
}
}