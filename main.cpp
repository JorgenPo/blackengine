#include "src/core/blapplication.h"
#include "src/core/blresourcemanager.h"
#include "src/core/bltexture.h"
#include "src/core/blmesh.h"

#include <QApplication>

using namespace black;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCursor::setPos(Constants::WIDTH / 2, Constants::HEIGHT / 2);
    QApplication::setOverrideCursor(Qt::BlankCursor);

    BLApplication application;
    application.showFullScreen();

    return a.exec();
}
