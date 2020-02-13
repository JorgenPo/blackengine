#include "mainwindow.h"
#include "renderwindow.h"
#include "widgets/LightSettingsWidget.h"

#include <BlackEngine/Engine.h>

#include <QTimer>
#include <QDockWidget>
#include <QtWidgets/QColorDialog>
#include <QtWidgets/QMessageBox>


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
    setUpSignals();
    setUpMenus();
}

void MainWindow::setUpSignals() {
//    connect(ui->hsLightIntensity, &QSlider::valueChanged,this,[=](int value) {
//      renderWindow->getScene()->onLightIntensityChanged(static_cast<float>(value) / 100);
//    });
//
//    connect(ui->hsAmbientIntensity,  &QSlider::valueChanged, this, [=](int value) {
//      renderWindow->getScene()->onAmbientIntensityChanged(static_cast<float>(value) / 100);
//    });
//
//    connect(ui->cbDisableLight, &QCheckBox::clicked, this, [=]() {
//      renderWindow->getScene()->setLightEnabled(!ui->cbDisableLight->checkState());
//    });
//
//    connect(ui->actionContextVersion, &QAction::triggered, this, &MainWindow::showContextInfo);
//
//    connect(ui->btAmbientColor, &QPushButton::clicked, this, [this]() {
//      lightColorChanged(LightType::AMBIENT);
//    });
//
//    connect(ui->btLightColor, &QPushButton::clicked, this, [this]() {
//      lightColorChanged(LightType::DIRECTED);
//    });
}
void MainWindow::setUpDocks() {
  auto lightDock = new QDockWidget(tr("Light settings"), this);
  lightDock->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
  lightDock->setWidget(new LightSettingsWidget(renderWindow));

  addDockWidget(Qt::RightDockWidgetArea, lightDock);
}

void MainWindow::setUpMenus() {

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

void MainWindow::lightColorChanged(black::LightType lightType) {
//  QPushButton *button;
//
//  switch (lightType) {
//  case LightType::DIRECTED:
//    button = ui->btLightColor;
//    break;
//  case LightType::AMBIENT:
//    button = ui->btAmbientColor;
//    break;
//  default:
//    this->logger->warning("MainWindow::lightColorChanged failed to change light color lightType={}", lightType);
//    return;
//  }
//
//  const auto &palette = button->palette();
//  const auto &oldColor = palette.color(QPalette::Button);
//  auto newColor = QColorDialog::getColor(
//      palette.color(QPalette::Button),
//      this,
//      "Choose new light color");
//
//  if (newColor == oldColor) {
//    return;
//  }
//
//  QPalette newPalette(palette);
//  newPalette.setColor(QPalette::Button, newColor);
//  button->setPalette(newPalette);
//
//  renderWindow->getScene()->onLightColorChanged(newColor, lightType);
}
