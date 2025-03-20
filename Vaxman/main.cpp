#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    srand(time(NULL));

    QApplication a(argc, argv);

    MainWindow::WIDTH = 600;
    MainWindow::HEIGHT = 600;

    MainWindow w;
    w.show();
    return a.exec();
}
