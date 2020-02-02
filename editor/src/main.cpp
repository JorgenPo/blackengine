#include "mainwindow.h"
#include "renderwindow.h"

#include <QApplication>
#include <BlackEngine/SystemInterface.h>

using namespace blackeditor;

class Application : public black::SystemInterface, public QApplication {
    std::shared_ptr<MainWindow> mainWindow;
    std::shared_ptr<RenderWindow> renderWindow;

public:
    Application(int &argc, char *argv[]) :
        QApplication(argc, argv),
        renderWindow(std::make_shared<RenderWindow>(nullptr))
    {
        mainWindow = std::make_shared<MainWindow>(renderWindow);
        renderWindow->setInput(mainWindow);
    }

    ~Application() override = default;

    // SystemInterface interfaceQApplication
public:
    [[nodiscard]] std::string getName() const override {
        return "qt";
    }

    SystemWindow createWindow(const black::WindowData &data) override {
        return {renderWindow, mainWindow};
    }

    void start() {
        mainWindow->start();
        mainWindow->show();
    }
};

int main(int argc, char *argv[])
{
    auto app = std::make_shared<Application>(argc, argv);

    black::Engine::RegisterSystemInterface(app);

    app->start();
    return app->exec();
}
