//
// Created by popov on 31.07.2019.
//

#ifndef BLACKENGINE_MOUSEEVENTLISTENER_H
#define BLACKENGINE_MOUSEEVENTLISTENER_H

#include "Mouse.h"

namespace black {

class MouseEventListener {
public:
  virtual void onMouseButtonEvent(MouseButtonEvent event) = 0;
  virtual void onMouseButtonPressed(MouseButtonEvent event) = 0;
  virtual void onMouseButtonReleased(MouseButtonEvent event) = 0;
};

}


#endif //BLACKENGINE_MOUSEEVENTLISTENER_H
