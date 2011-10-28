#include "MyQGraphicsView.h"
#include <QPointF>
#include <iostream>

MyQGraphicsView::MyQGraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    this->setSceneRect(50, 50, 350, 350);
    this->setScene(scene);
    this->setGeometry(QRect(20, 50, 400, 400));
}

void MyQGraphicsView::mousePressEvent(QMouseEvent *e)
{
    PointList *pl = PointList::getInstance();
    double rad = 2;

    QPointF pt = mapToScene(e->pos());
    Point *p = new Point(pt.x(), pt.y());

    this->drawPoint(p);
    pl->addPoint(p);
}

void MyQGraphicsView::drawPoint(Point *p, QColor color)
{
    QPen pen;
    pen.setColor(color);
    scene->addEllipse(p->getX(), p->getY(), 4, 4, pen, QBrush(Qt::SolidPattern));
    std::cout << "Adding point at " << p->getX() << ", " << p->getY() << std::endl;
}

void MyQGraphicsView::colourCluster(Cluster *c)
{

    for (vector<Point *>::iterator it = c->getPoints().begin(); it != c->getPoints().end(); ++ it)
    {
        drawPoint(*it, c->getColour());
    }
}
