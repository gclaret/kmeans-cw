#include "MyQGraphicsView.h"
#include <QPointF>
#include <iostream>

MyQGraphicsView::MyQGraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene(50, 50, 350, 350);
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

void MyQGraphicsView::drawPoint(Point *p, QColor color, bool clear, int size)
{
    QPen pen;
    if (clear)
    {
        pen.setColor(QColor(255, 255, 255));
    }
    else
    {
        pen.setColor(color);
    }
    scene->addEllipse(p->getX(), p->getY(), size, size, pen, QBrush(color));
}

void MyQGraphicsView::drawCluster(Cluster *c, bool clear)
{
    Point *p = c->getCentroid();
    QPen pen;
    if (clear)
    {
        pen.setColor(QColor(255, 255, 255));
    }
    else
    {
        pen.setColor(c->getColour());
    }

    // first line of cross.
    scene->addLine(p->getX(), p->getY(), p->getX() + 3, p->getY() + 3, pen);
    // second line of cross.
    scene->addLine(p->getX(), p->getY() + 3, p->getX() + 3, p->getY(), pen);
}

void MyQGraphicsView::colourCluster(Cluster *c)
{

    for (vector<Point *>::iterator it = c->getPoints()->begin(); it != c->getPoints()->end(); ++ it)
    {
        drawPoint(*it, c->getColour(), 10);
    }
}

// i don't think i'm actually using this anymore..
void MyQGraphicsView::delayedColourClusters(std::vector<Cluster *> &clusters)
{
    cluster_state = clusters;
    // timer...
    QTimer *timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(colourClusters()));
    timer->singleShot(3000, this, SLOT(colourClusters()));
}

void MyQGraphicsView::colourClusters()
{
    for (vector<Cluster *>::iterator it = cluster_state.begin(); it != cluster_state.end(); ++it)
    {
        colourCluster(*it);
    }
}

QGraphicsScene *MyQGraphicsView::getScene()
{
    return scene;
}

