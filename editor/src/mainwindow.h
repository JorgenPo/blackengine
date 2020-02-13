#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <BlackEngine/application/GameApplication.h>
#include <BlackEngine/input/InputSystemInterface.h>
#include <BlackEngine/SystemInterface.h>
#include <BlackEngine/input/Keyboard.h>

#include "widgets/ContextInfoWidget.h"

namespace blackeditor {
class RenderWindow;

class MainWindow : public QMainWindow, public black::AbstractApplication, public black::InputSystemInterface {
Q_OBJECT

  std::shared_ptr<RenderWindow> renderWindow;
  std::shared_ptr<black::PerformanceCounter> timer;

  std::unique_ptr<QTimer> updateTimer;

  std::unique_ptr<ContextInfoWidget> contextInfoWidget;

  QPointF cursorPosition;
public:
  explicit MainWindow(std::shared_ptr<RenderWindow> renderWindow);
  ~MainWindow() override;

public:
  bool isKeyPressed(black::Key key) override;
  bool isKeyPressed(int key) override;
  bool isKeyReleased(black::Key key) override;
  bool isKeyReleased(int key) override;
  void setCursorMode(black::CursorMode mode) override;
  void setMouseAccelerated(bool accelerated) override;
  void addCursor(std::string name, const black::Image &image) override;
  void setCursor(std::string name) override;
  float getMouseX() const noexcept override;
  float getMouseY() const noexcept override;
  bool isMouseButtonPressed(MouseButton button) const override;
  void onEvent(const MouseButtonEvent &event) override;
  float getScrollX() const override;
  float getScrollY() const override;

  // AbstractApplication interface
protected:
  void update(float dt) override;
  void init() override;
  void keyPressEvent(QKeyEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
private:
  void initializeResources() override;
  void run() override;

public slots:
  void onUpdateTime();
  void showContextInfo();
  void lightColorChanged(black::LightType lightType);
  void setUpSignals();
  void setUpDocks();
  void setUpMenus();

  //void onLightIntensityChanged(double newIntensity);
};

}

#endif // MAINWINDOW_H
