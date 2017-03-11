#include "src/core/blapplication.h"
#include "src/core/blmesh.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    BLApplication application;
    application.show();

    return a.exec();
}
