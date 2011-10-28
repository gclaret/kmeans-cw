#include "Cluster.h"

Cluster::Cluster(QColor c)
{
    double centroid;
    number_of_points = 0;
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

int Cluster::getNumberOfPoints()
{
    return number_of_points;
}

void Cluster::clearPoints()
{
    points.clear();

}

vector<Point *> Cluster::getPoints()
{
    return points;
}


void Cluster::computeConvexHull()
{

}

QColor Cluster::getColour()
{
    return colour;
}

void Cluster::addPoint(Point *p)
{
    points.push_back(p);
}

void Cluster::removePoint(Point *p)
{
    for (vector<Point *>::iterator it = points.begin(); it != points.end(); ++ it)
    {
        if (*(*it) == *p)
        {
            points.erase(it);
            return;
        }
    }
}
