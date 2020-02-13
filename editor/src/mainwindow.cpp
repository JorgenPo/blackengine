#include "mainwindow.h"
#include "renderwindow.h"
#include "widgets/LightSettingsWidget.h"
#include "widgets/ContextInfoWidget.h"

#include <BlackEngine/Engine.h>

#include <QTimer>
#include <QDockWidget>
#include <QColorDialog>
#include <QMessageBox>
#include <QMenuBar>

using namespace black;
using namespace blackeditor;

MainWindow::MainWindow(std::shared_ptr<RenderWindow> window)
    : QMainWindow(nullptr)
    , AbstractApplication("BlackEngine", 800, 600, false)
    , renderWindow(std::move(window))
    , updateTimer(std::make_unique<QTimer>(this))
    , contextInfoWidget(nullptr)
{
    setCentralWidget(renderWindow.get());
    setFixedWidth(800);
    setFixedHeight(600);

    // Setup update timer
    auto timerPtr = updateTimer.get();
    connect(timerPtr, SIGNAL(timeout()), this, SLOT(onUpdateTime()));
    timerPtr->start();

    Logger::SetLogLevel(LogLevel::TRACE);

    setUpDocks();
    setUpMenus();
    setUpSignals();
}

void MainWindow::setUpSignals() {

}

void MainWindow::setUpDocks() {
  auto lightDock = new QDockWidget(tr("Light settings"), this);
  lightDock->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);

  lightSettings = new LightSettingsWidget(renderWindow);

  lightDock->setWidget(lightSettings);
  addDockWidget(Qt::RightDockWidgetArea, lightDock);

  menuBar()->addMenu(tr("View"))->addAction(lightDock->toggleViewAction());
}

void MainWindow::setUpMenus() {
  auto menu = menuBar();
  auto about = menu->addMenu(tr("About"));
  auto contextInfoAction = about->addAction(tr("Context Info"));

  connect(contextInfoAction, &QAction::triggered, this, &MainWindow::showContextInfo);
}

MainWindow::~MainWindow() {
  setCentralWidget(nullptr);
  Logger::Get("MainWindow")->info("Render window ptr = {}", (uint64_t)renderWindow.get());
  Logger::Get("MainWindow")->info("Render window ptr counter = {}", renderWindow.use_count());
};

bool MainWindow::isKeyPressed(black::Key key)
{
    return false;
}

bool MainWindow::isKeyPressed(int key)
{
    return false;
}

bool MainWindow::isKeyReleased(black::Key key)
{
    return false;
}

bool MainWindow::isKeyReleased(int key)
{
    return false;
}

void MainWindow::setCursorMode(black::CursorMode mode)
{
}

void MainWindow::setMouseAccelerated(bool accelerated)
{
}

void MainWindow::addCursor(std::string name, const black::Image &image)
{
}

void MainWindow::setCursor(std::string name)
{
}

void MainWindow::update(float dt)
{
    this->cursorPosition = renderWindow->mapFromGlobal(QCursor::pos());
}

void MainWindow::init()
{
    auto renderSystem = Engine::GetCurrentRenderSystem();
    timer = std::make_shared<PerformanceCounter>();
}

void MainWindow::initializeResources()
{
}

void MainWindow::run()
{

}

void MainWindow::onUpdateTime()
{
    this->update(0);
    renderWindow->updateRenderTarget();
}

float MainWindow::getMouseX() const noexcept {
    return cursorPosition.x();
}

float MainWindow::getMouseY() const noexcept {
    return cursorPosition.y();
}

void MainWindow::onEvent(const MouseButtonEvent &event) {

}

void MainWindow::showContextInfo() {
  if (contextInfoWidget == nullptr) {
    contextInfoWidget = std::make_unique<ContextInfoWidget>(
        nullptr,
        renderWindow);
  }

  contextInfoWidget->show();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  renderWindow->getScene()->keyPressEvent(event);
}

float MainWindow::getScrollX() const {
  return 0;
}
float MainWindow::getScrollY() const {
  return 0;
}

bool MainWindow::isMouseButtonPressed(MouseButton button) const {
  return false;
}

std::optional<MouseButton> toBlackengineButton(Qt::MouseButton button) {
  switch (button) {
  case Qt::MouseButton::LeftButton:
    return MouseButton::LEFT;
  case Qt::MouseButton::RightButton:
    return MouseButton::RIGHT;
  case Qt::MouseButton::MiddleButton:
    return MouseButton::MIDDLE;
  default:
      return {};
  }
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
  auto button = toBlackengineButton(event->button());
  if (!button.has_value()) {
    this->logger->warning("Unsupported mouse button event. Mouse button {} pressed.", event->button());
    return;
  }

  this->publishMouseButtonEvent(
      MouseButtonEvent{
        button.value(),
        MouseButtonAction::PRESSED,
        0
      });
}

void MainWindow::onSceneInitialized() {
  lightSettings->setLightIntensity(LightType::AMBIENT, 40);
  lightSettings->setLightIntensity(LightType::DIRECTED, 40);
}
