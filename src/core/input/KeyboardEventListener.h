//
// Created by popov on 31.07.2019.
//

#ifndef BLACKENGINE_KEYBOARDEVENTLISTENER_H
#define BLACKENGINE_KEYBOARDEVENTLISTENER_H

#include "Keyboard.h"
#include <Exported.h>

namespace black {

/**
 * Listen for keyboard events
 */
class BLACK_EXPORTED KeyboardEventListener {
public:
  /**
   * Key press event
   * @param key Pressed key
   */
  virtual void onKeyEvent(KeyEvent keyEvent) = 0;
  virtual void onKeyPressed(KeyEvent keyEvent) = 0;
  virtual void onKeyReleased(KeyEvent keyEvent) = 0;
  virtual void onKeyRepeat(KeyEvent keyEvent) = 0;
};

}


#endif //BLACKENGINE_KEYBOARDEVENTLISTENER_H
