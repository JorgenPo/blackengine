//
// Created by popof on 02.10.2018.
//

#ifndef BLACKENGINE_ABSTRACTAPPLICATION_H
#define BLACKENGINE_ABSTRACTAPPLICATION_H

#include <common/CommonHeaders.h>

#include <exceptions/Exception.h>
#include <log/Logger.h>

namespace black {

class BLACK_EXPORTED ApplicationInitializationException : public Exception {
public:
  explicit ApplicationInitializationException(const std::string &message);
};

/**
 * Abstract engine application.
 * Concrete subclasses must define some special application loop and window counts.
 */
class BLACK_EXPORTED AbstractApplication {
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

  virtual void init();

private:
  /**
   * Init all resources
   */
  virtual void initializeResources() = 0;

  /**
   * Start an application
   */
  virtual void run() = 0;
};
}

#endif //BLACKENGINE_ABSTRACTAPPLICATION_H
