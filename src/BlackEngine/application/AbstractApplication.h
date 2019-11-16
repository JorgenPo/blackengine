//
// Created by popof on 02.10.2018.
//

#ifndef BLACKENGINE_ABSTRACTAPPLICATION_H
#define BLACKENGINE_ABSTRACTAPPLICATION_H

#include <BlackEngine/common/CommonHeaders.h>

#include <BlackEngine/exceptions/Exception.h>
#include <BlackEngine/log/Logger.h>

#include <BlackEngine/input/KeyboardEventListener.h>
#include <BlackEngine/input/MouseEventListener.h>

namespace black {

class BLACK_EXPORTED ApplicationInitializationException : public Exception {
public:
  explicit ApplicationInitializationException(const std::string &message);
};

/**
 * Abstract engine application.
 * Concrete subclasses must define some special application loop and window counts.
 */
class BLACK_EXPORTED AbstractApplication : protected KeyboardEventListener, protected MouseEventListener {
protected:
  std::string name;
  std::shared_ptr<Logger> logger;
  int windowWidth;
  int windowHeight;
  bool isWindowFullScreen;

public:
  explicit AbstractApplication(const std::string &name, int windowWidth, int windowHeight, bool isFullScreen);
  virtual ~AbstractApplication();

  [[nodiscard]] const std::string &getName() const;

  /**
   * Run the application.
   */
  void start();

  void setName(const std::string &name);

  [[nodiscard]] int getWindowWidth() const;

  void setWindowWidth(int windowWidth);

  [[nodiscard]] int getWindowHeight() const;

  void setWindowHeight(int windowHeight);

  [[nodiscard]] bool isFullScreen() const;

  void setFullScreen(bool isFullScreen);
protected:
  /**
  * Update game logic and scene
  */
  virtual void update(float dt) = 0;

  virtual void init() = 0;

  // Default implementation (stub) for key and mouse events
  // override it to handle events
  void onKeyEvent(KeyEvent keyEvent) override;
  void onKeyPressed(KeyEvent keyEvent) override;
  void onKeyReleased(KeyEvent keyEvent) override;
  void onKeyRepeat(KeyEvent keyEvent) override;

  void onMouseButtonEvent(MouseButtonEvent event) override;
  void onMouseButtonPressed(MouseButtonEvent event) override;
  void onMouseButtonReleased(MouseButtonEvent event) override;

private:
  /**
   * Init all resources
   */
  virtual void initializeResources() = 0;

  /**
   * Start an application
   */
  virtual void run() = 0;

  void initEngine();
};
}

#endif //BLACKENGINE_ABSTRACTAPPLICATION_H
