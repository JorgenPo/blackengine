//
// Created by popov on 31.07.2019.
//

#ifndef BLACKENGINE_MOUSEEVENTEMITTER_H
#define BLACKENGINE_MOUSEEVENTEMITTER_H

#include "Mouse.h"
#include <Exported.h>

#include <vector>

namespace black {

class MouseEventListener;

class BLACK_EXPORTED MouseEventEmitter {
  std::vector<MouseEventListener*> listeners;

public:
  void listenForMouseEvents(MouseEventListener *listener);

  void emitMouseButtonEvent(MouseButtonEvent event);
};

}


#endif //BLACKENGINE_MOUSEEVENTEMITTER_H
