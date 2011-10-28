#ifndef MYQGRAPHICSVIEW_H
#define MYQGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QMouseEvent>
#include "PointList.h"
#include "Cluster.h"

class MyQGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyQGraphicsView(QWidget *parent = 0);
    void drawPoint(Point *p, QColor color = QColor("black"));
    void colourCluster(Cluster *c);

signals:

public slots:
    void mousePressEvent(QMouseEvent *e);

private:
    QGraphicsScene *scene;
};

#endif // MYQGRAPHICSVIEW_H
