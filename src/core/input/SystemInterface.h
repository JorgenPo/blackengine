//
// Created by popof on 19.11.2018.
//
#ifndef BLACKENGINE_SYSTEMINTERFACE_H
#define BLACKENGINE_SYSTEMINTERFACE_H

#include "Keyboard.h"
#include "KeyboardEventEmitter.h"
#include "MouseEventEmitter.h"

#include <Exported.h>
#include <functional>

namespace black {

class Image;

/**
* Interface of the system. Handle the operating system events.
*/
class BLACK_EXPORTED SystemInterface : public KeyboardEventEmitter, public MouseEventEmitter {
public:
  virtual bool isKeyPressed(Key key) = 0;
  virtual bool isKeyPressed(int key) = 0;
  virtual bool isKeyReleased(Key key) = 0;
  virtual bool isKeyReleased(int key) = 0;
  virtual void setCursorMode(CursorMode mode) = 0;
  virtual void setMouseAccelerated(bool accelerated) = 0;

  virtual void addCursor(std::string name, const Image &image) = 0;
  virtual void setCursor(std::string name) = 0;
};
}
#endif //BLACKENGINE_SYSTEMINTERFACE_H
