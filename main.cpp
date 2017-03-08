#include "src/core/blapplication.h"
#include "src/mesh.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    BLApplication application;
    application.show();

    return a.exec();
}
