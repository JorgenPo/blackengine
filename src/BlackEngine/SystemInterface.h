//
// Created by popov on 18.10.2019.
//

#ifndef BLACKENGINE_SYSTEMINTERFACE_H
#define BLACKENGINE_SYSTEMINTERFACE_H

#include <memory>

namespace black {

class AbstractRenderWindow;
class InputSystemInterface;
class WindowData;

/**
 * Abstraction of operating system. Must support creation of a window.
 */
class SystemInterface {
public:
  struct SystemWindow {
    std::shared_ptr<AbstractRenderWindow> window;
    std::shared_ptr<InputSystemInterface> inputSystem;
  };

  [[nodiscard]] virtual std::string getName() const = 0;
  virtual SystemWindow createWindow(const WindowData &data) = 0;
};

}

#endif //BLACKENGINE_SYSTEMINTERFACE_H
