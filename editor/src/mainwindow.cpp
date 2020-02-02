#include "mainwindow.h"
#include "renderwindow.h"

#include "./ui_mainwindow.h"

#include <BlackEngine/Engine.h>

#include <QTimer>
#include <QtWidgets/QMessageBox>

using namespace black;
using namespace blackeditor;

MainWindow::MainWindow(std::shared_ptr<RenderWindow> window)
    : QMainWindow(nullptr)
    , AbstractApplication("BlackEngine", this->width(), this->height(), false)
    , renderWindow(std::move(window))
    , updateTimer(std::make_unique<QTimer>(this))
    , ui(new Ui::MainWindow)
    , contextInfoWidget(nullptr)
{
    ui->setupUi(this);

    // Substitute OpenGL widget with render window
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(renderWindow->sizePolicy().hasHeightForWidth());
    renderWindow->setSizePolicy(sizePolicy);

//    ui->gridLayout->setColumnStretch(0, 2);
//    ui->gridLayout->setColumnStretch(1, 1);

    ui->gridLayout->removeItem(ui->verticalSpacer);
    ui->gridLayout->addWidget(renderWindow.get(), 0, 0);

    // Setup update timer
    auto timerPtr = updateTimer.get();
    connect(timerPtr, SIGNAL(timeout()), this, SLOT(onUpdateTime()));
    timerPtr->start();

    Logger::SetLogLevel(LogLevel::TRACE);

    connect(ui->hsLightIntensity, &QSlider::valueChanged,this,[=](int value) {
      renderWindow->getScene()->onLightIntensityChanged(static_cast<float>(value) / 100);
    });

    connect(ui->hsAmbientIntensity,  &QSlider::valueChanged, this, [=](int value) {
      renderWindow->getScene()->onAmbientIntensityChanged(static_cast<float>(value) / 100);
    });

    connect(ui->cbDisableLight, &QCheckBox::clicked, this, [=]() {
      renderWindow->getScene()->setLightEnabled(!ui->cbDisableLight->checkState());
    });

    connect(ui->actionContextVersion, &QAction::triggered, this, &MainWindow::showContextInfo);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::onLightIntensityChanged(double newIntensity) {
//  Logger::Get("editor")->trace("New intensity: {}", newIntensity);
//}

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
