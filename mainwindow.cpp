#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "KMeansClustering.h"
#include <iostream>
#include <QGridLayout>

#define TESTING 0

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    my_view = new MyQGraphicsView();
    ui->gridLayout->addWidget(my_view);
    ui->converged_label->hide();
    ui->kmeans_button->setChecked(true);
    kmc = NULL;


    clustering_begun = false;

    if (TESTING)
    {

        int steps, k;
        bool converged;

        for (k = 2; k < 8; k++)
        {
            // regular k-means.
            import();
            converged = false;
            steps = 0;

            kmc = new KMeansClustering(k, PointList::getInstance(), KMEANS);

            while (!converged)
            {
                converged = kmc->naiveStep();
                steps++;
            }
            cout << "k = " << k << ", regular k-means, cost = " << kmc->getCost() << ", steps = " << steps << endl;


            // k-means++
            import();
            converged = false;
            steps = 0;

            kmc = new KMeansClustering(k, PointList::getInstance(), KMEANS_PLUSPLUS);
            while (!converged)
            {
                converged = kmc->naiveStep(my_view);
                steps++;
            }
            cout << "k = " << k << ", k-means++, cost = " << kmc->getCost() << ", steps = " << steps << endl;


            // k-means#
            import();
            converged = false;
            steps = 0;

            kmc = new KMeansClustering(k, PointList::getInstance(), KMEANS_SHARP);
            while (!converged)
            {
                converged = kmc->naiveStep(my_view);
                steps++;
            }
            cout << "k = " << k << ", k-means#, cost = " << kmc->getCost() << ", steps = " << steps << endl;

        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::kmeansButtonPushHandler()
{
    bool converged = false;
    int k = ui->k_value_input->text().toInt();

    if (!clustering_begun)
    {
        if (ui->kmeans_button->isChecked())
        {
            // k-means
            kmc = new KMeansClustering(k, PointList::getInstance(), KMEANS);
        }
        else if (ui->kmeans_plusplus_button->isChecked())
        {
            // k-means++
            kmc = new KMeansClustering(k, PointList::getInstance(), KMEANS_PLUSPLUS);
        }
        else
        {
            kmc = new KMeansClustering(k, PointList::getInstance(), KMEANS_SHARP);
        }

        converged = kmc->naiveStep(my_view);
        clustering_begun = true;
    }
    else
    {
        converged = kmc->naiveStep(my_view);
        if (converged)
        {
            ui->converged_label->show();
            cout << "Cost: " << kmc->getCost() << endl;
        }
        else
        {
            ui->converged_label->hide();
        }
    }
}

void MainWindow::numberOfPointsHandler()
{
    int num_pts = 0;
    num_pts = ui->horizontalSlider->value();

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

void MainWindow::reset()
{
    PointList *pl = PointList::getInstance();
    for (vector<Point *>::iterator it = pl->begin(); it != pl->end(); ++it)
    {
        my_view->drawPoint((*it), QColor(255, 255, 255), true); // clear points drawn
    }
    pl->clear();
    ui->converged_label->hide();
    clustering_begun = false;
    if (kmc != NULL)
    {
        kmc->removeClusters(my_view);
    }
}

void MainWindow::import()
{
    reset();
    ifstream input("points.txt");
    string line_data;

    PointList *pl = PointList::getInstance();
    while (getline(input, line_data))
    {
        double x, y;
        char comma;
        stringstream line_stream(line_data);

        // read points in.
        if (line_stream >> x >> comma >> y)
        {
            Point *p = new Point(x, y);
            pl->addPoint(p);
            my_view->drawPoint(p, QColor("cyan"));
        }
     }
}

void MainWindow::savePoints()
{
    ofstream out("points.txt");
    if (!out)
    {
        cout << "Could not open file." << endl;
    }

    PointList *pl = PointList::getInstance();
    for (vector<Point *>::iterator it = pl->begin(); it != pl->end(); ++it)
    {
        out << (*it)->getX() << ", " << (*it)->getY() << endl;
    }
    out.close();
    cout << "ok done saving." << endl;
}
