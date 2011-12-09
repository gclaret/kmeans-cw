#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "KMeansClustering.h"
#include <iostream>
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    my_view = new MyQGraphicsView();
    ui->gridLayout->addWidget(my_view);
    //std::cout << "height = " << ui->gridLayout->geometry().height() << std::endl;

    PointList *pl = PointList::getInstance();
    Point *p1, *p2;

    p1 = new Point(0, 0);
    pl->addPoint(p1);
    my_view->drawPoint(p1);

    p2 = new Point(350, 350);
    pl->addPoint(p2);
    my_view->drawPoint(p2);

    clustering_begun = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::kmeansButtonPushHandler()
{
    bool converged = false;
    if (!clustering_begun)
    {
        kmc = new KMeansClustering(3, PointList::getInstance());
        converged = kmc->naiveStep(my_view);
        clustering_begun = true;
    }
    else
    {

        std::cout << "clustering begun is true" << std::endl;
        converged = kmc->naiveStep(my_view);
    }
}

void MainWindow::numberOfPointsHandler()
{
    int num_pts = 0;
    num_pts = ui->horizontalSlider->value();
   // std::cout << "num_pts = " << num_pts << std::endl;

    PointList *pl = PointList::getInstance();
    int x_coord, y_coord;

    for (int i = 0; i < num_pts; i++)
    {
        x_coord = rand() % (int)my_view->getScene()->width();
        y_coord = rand() % (int)my_view->getScene()->height();

        Point *p = new Point(x_coord, y_coord);
        pl->addPoint(p);
        my_view->drawPoint(p, QColor("cyan"));
    }

    clustering_begun = false;

}
