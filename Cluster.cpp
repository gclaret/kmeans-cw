#include "Cluster.h"

Cluster::Cluster(QColor c, int id)
{
    this->id = id;
    this->colour = c;
    points = new vector<Point *>();
    randomInit();
}

Cluster::Cluster(QColor c, int id, double _x, double _y)
{
    this->id = id;
    this->colour = c;
    points = new vector<Point *>();
    centroid = new Point(_x, _y);
}

Cluster::~Cluster()
{
    delete centroid;
    points->clear();
}

void Cluster::randomInit()
{
    int x_coord = rand() % 350;
    int y_coord = rand() % 350;

    centroid = new Point(x_coord, y_coord);
}

Point *Cluster::getCentroid()
{
    return centroid;
}

void Cluster::updateCentroid()
{
    int count = 0;
    double x_sum = 0.0;
    double y_sum = 0.0;
    for (std::vector<Point *>::iterator it = points->begin(); it != points->end(); ++it)
    {
        x_sum += (*it)->getX();
        y_sum += (*it)->getY();
        count++;
    }

    // need to account for if we have no points better than this.  delete the cluster maybe or reallocate it randomly [TODO]
    if (count == 0)
    {
        centroid->setX(0);
        centroid->setY(0);
    }
    else
    {
        centroid->setX(x_sum/count);
        centroid->setY(y_sum/count);
    }

    points->clear();
}

int Cluster::getNumberOfPoints() const
{
    return points->size();
}

void Cluster::clearPoints()
{
    points->clear();

}

vector<Point *> *Cluster::getPoints() const
{
    return points;
}

QColor Cluster::getColour() const
{
    return colour;
}

void Cluster::addPoint(Point *p)
{
    points->push_back(p);
    /*for (vector<Point *>::iterator it = points->begin(); it != points->end(); ++it)
    {
        cout << (*it)->getX() << ", " << (*it)->getY() << endl;
    }*/
}

void Cluster::removePoint(Point *p)
{
    for (vector<Point *>::iterator it = points->begin(); it != points->end(); ++ it)
    {
        if (*(*it) == *p)
        {
            points->erase(it);
            return;
        }
    }
}

ostream &operator<<(ostream &output, const Cluster &c)
{
    output << "[";
    for (vector<Point *>::iterator it = c.getPoints()->begin(); it != c.getPoints()->end(); ++ it)
    {
        output << *(*it) << ", ";
    }
    output << "]";
    return output;
}
