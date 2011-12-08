#ifndef POINT_H
#define POINT_H

#include <math.h>
#include <iostream>
using std::ostream;

class Point
{
public:
    Point();
    Point(double x, double y);

    double getX() const;
    double getY() const;
    double euclideanDistance(Point *pt);
    void setX(double x);
    void setY(double y);
    int getCluster() const;
    int setCluster(int c);

    bool operator==(const Point &p) const;
    friend ostream &operator<<(ostream &output, const Point &p);
private:
    double x;
    double y;
    int cluster;
};

#endif // POINT_H
