#ifndef MYQGRAPHICSVIEW_H
#define MYQGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QMouseEvent>
#include <QTimer>
#include "PointList.h"
#include "Cluster.h"

class MyQGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyQGraphicsView(QWidget *parent = 0);
    void drawPoint(Point *p, QColor color = QColor("black"), bool clear= false, int size = 4);
    void drawCluster(Cluster *c, bool clear = false);
    void colourCluster(Cluster *c);
    QGraphicsScene *getScene();
    void delayedColourClusters(std::vector<Cluster *> &clusters);

signals:

public slots:
    void mousePressEvent(QMouseEvent *e);
    void colourClusters();

private:
    QGraphicsScene *scene;
    std::vector<Cluster *> cluster_state;

};

#endif // MYQGRAPHICSVIEW_H
