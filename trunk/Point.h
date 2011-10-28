#ifndef POINT_H
#define POINT_H

#include <math.h>

class Point
{
public:
    Point();
    Point(double x, double y);

    double getX();
    double getY();
    double euclideanDistance(Point *pt);
    void setX(double x);
    void setY(double y);

    bool operator==(const Point &p) const;
private:
    double x;
    double y;
};

#endif // POINT_H
