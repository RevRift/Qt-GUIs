#include "mainwindow.h"

#include <QApplication>
#include <algorithm>

/*
 * Transition from one page to another
 * flash red or green when answering questions wrong/correctly
*/

int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);

    QFile styles(":/design/styles.qss");
    if(styles.open(QIODevice::ReadOnly | QIODevice::Text)) {
        a.setStyleSheet(styles.readAll());
        styles.close();
    }
    MainWindow w;
    w.show();
    return a.exec();
}
