//
// Created by popov on 31.07.2019.
//

#ifndef BLACKENGINE_KEYBOARDEVENTSUBSCRIBER_H
#define BLACKENGINE_KEYBOARDEVENTSUBSCRIBER_H

#include "Keyboard.h"
#include "../Exported.h"

#include <BlackEngine/common/events/EventSubscriber.h>

namespace black {

/**
 * Listen for keyboard events
 */
class BLACK_EXPORTED KeyboardEventSubscriber : public EventSubscriber<KeyEvent> {
public:
  /**
   * Key press event
   * @param key Pressed key
   */
  virtual void onKeyEvent(KeyEvent keyEvent) = 0;
  virtual void onKeyPressed(KeyEvent keyEvent) = 0;
  virtual void onKeyReleased(KeyEvent keyEvent) = 0;
  virtual void onKeyRepeat(KeyEvent keyEvent) = 0;

private:
  void onEvent(const KeyEvent &event) override {
    onKeyEvent(event);

    switch (event.action) {
      case KeyAction::PRESSED:
        onKeyPressed(event);
        break;
      case KeyAction::RELEASED:
        onKeyReleased(event);
        break;
      case KeyAction::REPEAT:
        onKeyRepeat(event);
        break;
    }
  }
};

}


#endif //BLACKENGINE_KEYBOARDEVENTSUBSCRIBER_H
