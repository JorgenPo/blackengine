#ifndef BLACKENGINE_GLFWSYSTEMINTERFACE_H
#define BLACKENGINE_GLFWSYSTEMINTERFACE_H

#include <BlackEngine/SystemInterface.h>

namespace black {

/**
 * GLFW system interface implementation
 */
class GLFWSystemInterface : public SystemInterface {
public:
  [[nodiscard]] std::string getName() const override;

  SystemWindow createWindow(const WindowData &data) override;
};

}

#endif //BLACKENGINE_GLFWSYSTEMINTERFACE_H
