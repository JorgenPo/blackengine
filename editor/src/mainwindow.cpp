#include "mainwindow.h"
#include "renderwindow.h"
#include "widgets/LightSettingsWidget.h"
#include "widgets/ContextInfoWidget.h"
#include "widgets/ObjectInfoWidget.h"

#include <BlackEngine/Engine.h>

#include <QTimer>
#include <QDockWidget>
#include <QColorDialog>
#include <QMessageBox>
#include <QMenuBar>
#include <QSize>
#include <QResizeEvent>

using namespace black;
using namespace blackeditor;

MainWindow::MainWindow(std::shared_ptr<RenderWindow> window)
    : QMainWindow(nullptr)
    , AbstractApplication("BlackEngine", 1280, 1024, false)
    , renderWindow(std::move(window))
    , updateTimer(std::make_unique<QTimer>(this))
    , contextInfoWidget(nullptr)
{
    setCentralWidget(renderWindow.get());
    setMinimumWidth(this->getWindowWidth());
    setMinimumHeight(this->getWindowHeight());

    // Setup update timer
    auto timerPtr = updateTimer.get();
    connect(timerPtr, SIGNAL(timeout()), this, SLOT(onUpdateTime()));
    timerPtr->start();

    Logger::SetLogLevel(LogLevel::TRACE);

    setUpDocks();
    setUpMenus();
    setUpSignals();

    cursors[CURSOR_HAND] = QCursor(Qt::CursorShape::OpenHandCursor);
    cursors[CURSOR_NORMAL] = QCursor(Qt::CursorShape::ArrowCursor);
    cursors[CURSOR_CLOSED_HAND] = QCursor(Qt::CursorShape::ClosedHandCursor);
}

void MainWindow::setUpSignals() {
}

void MainWindow::setUpDocks() {
  auto lightDock = new QDockWidget(tr("Light settings"), this);
  lightDock->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);

  lightSettings = new LightSettingsWidget(renderWindow);
  lightDock->setWidget(lightSettings);
  addDockWidget(Qt::RightDockWidgetArea, lightDock);

  auto objectInfoDock = new QDockWidget(tr("Object info"), this);
  objectInfoDock->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);

  objectInfo = new ObjectInfoWidget();
  objectInfoDock->setWidget(objectInfo);
  addDockWidget(Qt::LeftDockWidgetArea, objectInfoDock);

  auto viewMenu = menuBar()->addMenu(tr("View"));
  viewMenu->addAction(lightDock->toggleViewAction());
  viewMenu->addAction(objectInfoDock->toggleViewAction());
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
  logger->info("Add cursor name={}", name);
}

void MainWindow::setCursor(std::string name)
{
  if (auto cursor = cursors.find(name); cursor != cursors.end()) {
    QWidget::setCursor(cursor->second);
  } else {
    logger->warning("Failed to set cursor: name={}", name);
  }
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
    scrollDelta = {};
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
  return scrollDelta.x();
}
float MainWindow::getScrollY() const {
  return scrollDelta.y();
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

  connect(renderWindow->getScene().get(), &Scene::onObjectSelected, objectInfo, &ObjectInfoWidget::setObject);
}

void MainWindow::wheelEvent(QWheelEvent *event) {
  scrollDelta.setX((float) event->angleDelta().x() * scrollSpeed);
  scrollDelta.setY((float) event->angleDelta().y() * scrollSpeed);
}

void MainWindow::resizeEvent(QResizeEvent *event) {
  QWidget::resizeEvent(event);

//  const auto &size = event->size();
//  setWindowWidth(size.width());
//  setWindowWidth(size.height());
}
