#include "mainwindow.h"
#include "renderwindow.h"
#include "common/Util.h"
#include "widgets/LightSettingsWidget.h"
#include "widgets/ContextInfoWidget.h"
#include "widgets/ObjectInfoWidget.h"
#include "widgets/PerformanceInfoWidget.h"

#include <BlackEngine/Engine.h>
#include <BlackEngine/performance/PerformanceCounter.h>

#include <QTimer>
#include <QDockWidget>
#include <QMenuBar>
#include <QSize>
#include <QResizeEvent>
#include <QStatusBar>
#include <QtCore/QCoreApplication>

using namespace black;
using namespace blackeditor;

MainWindow::MainWindow(std::shared_ptr<RenderWindow> window)
    : QMainWindow(nullptr)
    , AbstractApplication("BlackEngine", 1280, 1024, false)
    , renderWindow(std::move(window))
    , timer(std::make_shared<PerformanceCounter>())
    , updateTimer(std::make_unique<QTimer>(this))
    , guiUpdateTimer(std::make_unique<QTimer>(this))
    , contextInfoWidget(nullptr)
{
    setCentralWidget(renderWindow.get());
    setMinimumWidth(this->getWindowWidth());
    setMinimumHeight(this->getWindowHeight());
    setFullScreen(true);

    // Setup update timer
    auto timerPtr = updateTimer.get();
    connect(timerPtr, SIGNAL(timeout()), this, SLOT(onUpdateTime()));
    timerPtr->setInterval(1000 / 30); // 30fps
    timerPtr->start();

    connect(guiUpdateTimer.get(), SIGNAL(timeout()), this, SLOT(onUpdateGuiTime()));
    guiUpdateTimer->setInterval(1000 / 4); // 4 fps
    guiUpdateTimer->start();

    Logger::SetLogLevel(LogLevel::TRACE);

    setUpMenus();
    setUpDocks();
    setUpSignals();

    cursors[CURSOR_HAND] = QCursor(Qt::CursorShape::OpenHandCursor);
    cursors[CURSOR_NORMAL] = QCursor(Qt::CursorShape::ArrowCursor);
    cursors[CURSOR_CLOSED_HAND] = QCursor(Qt::CursorShape::ClosedHandCursor);
}

void MainWindow::setUpSignals() {
}

void MainWindow::setUpDocks() {
  auto lightDock = new QDockWidget(tr("Light settings"), this);
  lightDock->setAllowedAreas(Qt::RightDockWidgetArea);

  lightSettings = new LightSettingsWidget(renderWindow);
  lightDock->setWidget(lightSettings);
  addDockWidget(Qt::RightDockWidgetArea, lightDock);
  lightDock->hide();

  objectInfoDock = new QDockWidget(tr("Object info"), this);
  objectInfoDock->setAllowedAreas(Qt::RightDockWidgetArea);

  objectInfo = new ObjectInfoWidget();
  objectInfoDock->setWidget(objectInfo);
  addDockWidget(Qt::RightDockWidgetArea, objectInfoDock);

  auto viewMenu = menuBar()->addMenu(tr("View"));
  viewMenu->addAction(lightDock->toggleViewAction());
  viewMenu->addAction(objectInfoDock->toggleViewAction());
}

void MainWindow::setUpMenus() {
  auto menu = menuBar();

  auto file = menu->addMenu(tr("File"));
  auto exitAction = file->addAction(tr("Exit"));
  exitAction->setShortcut(QKeySequence::Quit);
  connect(exitAction, &QAction::triggered, this, [](){
    QCoreApplication::exit(0);
  });

  auto about = menu->addMenu(tr("About"));
  auto contextInfoAction = about->addAction(tr("Context Info"));
  connect(contextInfoAction, &QAction::triggered, this, &MainWindow::showContextInfo);

  statusBar()->showMessage(tr("Ready"));

  performanceInfo = new PerformanceInfoWidget(timer);
  statusBar()->addPermanentWidget(performanceInfo);
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
}

void MainWindow::initializeResources()
{
}

void MainWindow::run()
{

}

void MainWindow::onUpdateTime()
{
    this->timer->update();
    this->update(0);
    renderWindow->updateRenderTarget();
    scrollDelta = {};
    this->timer->update();
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

void MainWindow::mousePressEvent(QMouseEvent *event) {
  auto blackEvent = toBlackengineMouseButtonEvent(event);
  if (blackEvent) {
    this->publishMouseButtonEvent(blackEvent.value());
  }
}

void MainWindow::onSceneInitialized() {
  lightSettings->setLightIntensity(LightType::AMBIENT, 40);
  lightSettings->setLightIntensity(LightType::DIRECTED, 40);

  connect(renderWindow->getScene().get(), &Scene::objectSelected, this, &MainWindow::objectSelected);
  connect(renderWindow->getScene().get(),
          &Scene::selectedObjectTransformed, objectInfo, &ObjectInfoWidget::updateObjectInfo);
}

void MainWindow::wheelEvent(QWheelEvent *event) {
  scrollDelta.setX((float) event->angleDelta().x() * scrollSpeed);
  scrollDelta.setY((float) event->angleDelta().y() * scrollSpeed);
}

void MainWindow::resizeEvent(QResizeEvent *event) {
  QWidget::resizeEvent(event);
}

void MainWindow::objectSelected(std::shared_ptr<black::GameObject> object) {
  if (object == nullptr) {
    statusBar()->showMessage(tr("Ready"));
    return;
  }

  statusBar()->showMessage(tr("Working with") + " " + object->getName().data());
  objectInfo->setObject(std::move(object));
}

void MainWindow::onUpdateGuiTime() {
  performanceInfo->updateInfo();
}
