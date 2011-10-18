#include <QtGui/QApplication>
#include "mainwindow.h"
#include "PointList.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    PointList pl;

    int x_coord, y_coord;
    for (int i = 0; i < 10; i++)
    {
        x_coord = rand() % 100;
        y_coord = rand() % 100;
        pl.addPoint(new Point(x_coord, y_coord));
    }


    w.show();

    return a.exec();
}
