#include "mainwindow.h"

#include <QApplication>

/*
 * Class trip is a trip of a where the teacher of a subject
 * and all the students go somewhere related to their class
*/

int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
