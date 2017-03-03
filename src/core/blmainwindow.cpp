#include "blmainwindow.h"
#include "ui_blmainwindow.h"

blMainWindow::blMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::blMainWindow)
{
    ui->setupUi(this);
}

blMainWindow::~blMainWindow()
{
    delete ui;
}
