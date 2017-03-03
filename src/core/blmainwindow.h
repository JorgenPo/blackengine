#ifndef BLMAINWINDOW_H
#define BLMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class blMainWindow;
}

class blMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit blMainWindow(QWidget *parent = 0);
    ~blMainWindow();

private:
    Ui::blMainWindow *ui;
};

#endif // BLMAINWINDOW_H
