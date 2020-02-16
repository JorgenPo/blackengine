#include "mainwindow.h"
#include "renderwindow.h"

#include <QApplication>
#include <BlackEngine/Engine.h>
#include <BlackEngine/SystemInterface.h>

using namespace blackeditor;

class QtSystemInterface : public black::SystemInterface {
  std::shared_ptr<MainWindow> mainWindow;
  std::shared_ptr<RenderWindow> renderWindow;

public:
  QtSystemInterface(std::shared_ptr<MainWindow> mainWindow, std::shared_ptr<RenderWindow> renderWindow)
    : mainWindow(std::move(mainWindow)), renderWindow(std::move(renderWindow)) {}

  [[nodiscard]] std::string getName() const override {
    return "qt";
  }
  SystemWindow createWindow(const WindowData &data) override {
    return {renderWindow, mainWindow};
  }
};

class Application : public QApplication {
    std::shared_ptr<QtSystemInterface> systemInterface;
    std::shared_ptr<MainWindow> mainWindow;

public:
    Application(int &argc, char *argv[]) :
        QApplication(argc, argv)
    {
        auto renderWindow = std::make_shared<RenderWindow>(nullptr);
        mainWindow = std::make_shared<MainWindow>(renderWindow);
        renderWindow->setMainWindow(mainWindow);
        renderWindow->setInput(mainWindow);
        systemInterface = std::make_shared<QtSystemInterface>(mainWindow, std::move(renderWindow));
    }

    ~Application() override {
//      Logger::Get("MainWindow")->info("Render window ptr = {}", (uint64_t)renderWindow.get());
//      Logger::Get("MainWindow")->info("Render window ptr counter = {}", renderWindow.use_count());
//      Logger::Get("MainWindow")->info("Main window ptr = {}", (uint64_t)mainWindow.get());
//      Logger::Get("MainWindow")->info("Main window ptr counter = {}", mainWindow.use_count());
    };

  [[nodiscard]] std::shared_ptr<QtSystemInterface> getSystemInterface() const {
    return systemInterface;
  }

  void start() {
        mainWindow->start();
        mainWindow->showFullScreen();
    }
};

int main(int argc, char *argv[])
{
    auto app = std::make_shared<Application>(argc, argv);

    black::Engine::RegisterSystemInterface(app->getSystemInterface());

    app->start();
    return app->exec();
}
