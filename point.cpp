#include "Point.h"

Point::Point()
{
    this->x = 0;
    this->y = 0;
}

Point::Point(double x, double y)
{
    this->x = x;
    this->y = y;
}

double Point::getX()
{
    return x;
}

double Point::getY()
{
    return y;
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
