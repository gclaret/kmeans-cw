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

void MyQGraphicsView::drawPoint(Point *p, QColor color, int size)
{
    QPen pen;
    pen.setColor(color);
  //  std::cout << "Drawing point: " << *p << std::endl;
    scene->addEllipse(p->getX(), p->getY(), size, size, pen, QBrush(Qt::SolidPattern));
  //  std::cout << "Adding point at " << p->getX() << ", " << p->getY() << std::endl;
}

void MyQGraphicsView::colourCluster(Cluster *c)
{
    std::cout << *c << endl;
    std::cout << "It's time to colour a cluster.  This cluster is centered at " << *(c->getCentroid()) << " ok." << std::endl;
    std::cout << "This cluster's size is " << c->getNumberOfPoints() << std::endl;

    for (vector<Point *>::iterator it = c->getPoints()->begin(); it != c->getPoints()->end(); ++ it)
    {
        std::cout << "This point we will colour is " << *(*it) << " and we are good. " << std::endl;
        drawPoint(*it, c->getColour(), 10);
    }
}

void MyQGraphicsView::delayedColourClusters(std::vector<Cluster *> &clusters)
{
    std::cout << "Pre timer" << std::endl;
    cluster_state = clusters;
    // timer...
    QTimer *timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(colourClusters()));
    timer->singleShot(3000, this, SLOT(colourClusters()));
    std::cout << "Post timer" << std::endl;
}

void MyQGraphicsView::colourClusters()
{
    std::cout << "Colouring clusters!" << std::endl;
    for (vector<Cluster *>::iterator it = cluster_state.begin(); it != cluster_state.end(); ++it)
    {
        colourCluster(*it);
    }
}

QGraphicsScene *MyQGraphicsView::getScene()
{
    return scene;
}
