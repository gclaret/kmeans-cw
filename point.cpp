#include "Point.h"

Point::Point()
{
    this->x = 0;
    this->y = 0;
}

Point::Point(int x, int y)
{
    this->x = x;
    this->y = y;
}

int Point::getX()
{
    return x;
}

int Point::getY()
{
    return y;
}

void Point::setX(int x)
{
    this->x = x;
}

void Point::setY(int y)
{
    this->y = y;
}

bool Point::operator==(const Point &p) const
{
    if (x != p.x || y != p.y) return false;
    return true;
}