#include "src/core/blapplication.h"
#include "src/core/blresourcemanager.h"
#include "src/core/bltexture.h"
#include "src/core/blmesh.h"

#include <QApplication>

using namespace black;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    BLApplication application;
    application.show();

    return a.exec();
}
