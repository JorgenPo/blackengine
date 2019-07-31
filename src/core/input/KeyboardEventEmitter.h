//
// Created by popov on 31.07.2019.
//

#ifndef BLACKENGINE_KEYBOARDEVENTEMITTER_H
#define BLACKENGINE_KEYBOARDEVENTEMITTER_H

#include "Keyboard.h"

#include <Exported.h>

#include <vector>
#include <memory>

namespace black {

class KeyboardEventListener;

/**
 * Emits keyboard events (key pressed)
 */
class BLACK_EXPORTED KeyboardEventEmitter {
  std::vector<KeyboardEventListener*> listeners;

public:
  void listenForKeyboardEvents(KeyboardEventListener *listener);

  void emitKeyPressedEvent(KeyEvent event);
};

}


#endif //BLACKENGINE_KEYBOARDEVENTEMITTER_H
