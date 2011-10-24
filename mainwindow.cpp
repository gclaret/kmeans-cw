#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "MyQGraphicsView.h"
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->gridLayout->addWidget(new MyQGraphicsView());

    /*QGraphicsScene *scene;
    QGraphicsView *view = new QGraphicsViewW(this);

    view->setGeometry(QRect(20, 50, 400, 400));
    scene = new QGraphicsScene(50, 50, 350, 350);
    view->setScene(scene);

    QGraphicsLineItem *line = new QGraphicsLineItem(10, 10, 50, 50);
    line->setFlag((QGraphicsItem::ItemIsMovable));
    scene->addItem(line);*/

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::numberOfPointsHandler()
{
    int num_pts = 0;
    num_pts = ui->horizontalSlider->value();
    std::cout << "num_pts = " << num_pts << std::endl;
}
