#ifndef POINTLIST_H
#define POINTLIST_H

#include <vector>
#include "Point.h"

using namespace std;
class PointList
{
public:
    PointList();
    PointList(Point *p);
    void addPoint(Point *p);
    void removePoint(Point *p);

private:
    vector< Point* > *pl;
};

#endif // POINTLIST_H
