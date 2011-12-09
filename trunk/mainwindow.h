#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include "PointList.h"
#include "MyQGraphicsView.h"
#include "KMeansClustering.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void numberOfPointsHandler();
    void kmeansButtonPushHandler();

private:
    Ui::MainWindow *ui;
    MyQGraphicsView *my_view;

    bool clustering_begun;
    KMeansClustering *kmc;
};

#endif // MAINWINDOW_H
