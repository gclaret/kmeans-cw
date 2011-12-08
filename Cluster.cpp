#include "Cluster.h"

Cluster::Cluster(QColor c, int id)
{
    this->id = id;
    this->colour = c;
    number_of_points = 0;
    points = new vector<Point *>();
    randomInit();
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

int Cluster::getNumberOfPoints() const
{
    return number_of_points;
}

void Cluster::clearPoints()
{
    points->clear();

}

vector<Point *> *Cluster::getPoints() const
{
    return points;
}


void Cluster::computeConvexHull()
{

}

QColor Cluster::getColour() const
{
    return colour;
}

void Cluster::addPoint(Point *p)
{
    std::cout << "Adding: " << *p << std::endl;
    points->push_back(p);
    std::cout << *this << std::endl;
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
