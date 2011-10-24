#ifndef POINTLIST_H
#define POINTLIST_H

#include <vector>
#include "Point.h"


// Making this a singleton object.
// Only one pointlist should exist at any one point in time.
using namespace std;
class PointList
{
public:

    static PointList *getInstance();
    void addPoint(Point *p);


private:
    vector< Point* > *pl;
    PointList();

    void removePoint(Point *p);

    static PointList *instance;
    static bool instance_created;
};

#endif // POINTLIST_H
