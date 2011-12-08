#include "Point.h"

Point::Point()
{
    this->x = 0;
    this->y = 0;
    this->cluster = -1;
}

Point::Point(double x, double y)
{
    this->x = x;
    this->y = y;
    this->cluster = -1;
}

double Point::getX() const
{
    return x;
}

double Point::getY() const
{
    return y;
}

int Point::getCluster() const
{
    return cluster;
}

int Point::setCluster(int c)
{
    cluster = c;
}


void Point::setX(double x)
{
    this->x = x;
}

void Point::setY(double y)
{
    this->y = y;
}

bool Point::operator==(const Point &p) const
{
    if (x != p.x || y != p.y) return false;
    return true;
}

ostream &operator<<(ostream &output, const Point &p)
{
        output << "(" << p.getX() << ", " << p.getY() << ")";
        return output;
}

double Point::euclideanDistance(Point *pt)
{
    double dist = 0.0;
    double x_dist = pow((pt->getX() - x), 2);
    double y_dist = pow((pt->getY() - y), 2);

    dist = sqrt(x_dist + y_dist);
    return dist;
}
