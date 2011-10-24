#include "MyQGraphicsView.h"
#include <QPointF>

MyQGraphicsView::MyQGraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    this->setSceneRect(50, 50, 350, 350);
    this->setScene(scene);
    this->setGeometry(QRect(20, 50, 400, 400));
}

/*
  Still to do here:  Add these newfound points to the point list.
  Render random points, rather than only mouse-clicked points.
  */
void MyQGraphicsView::mousePressEvent(QMouseEvent *e)
{
    double rad = 2;
    QPointF pt = mapToScene(e->pos());
    scene->addEllipse(pt.x() - rad, pt.y() - rad, rad * 2, rad * 2, QPen(), QBrush(Qt::SolidPattern));
}
