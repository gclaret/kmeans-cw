#include "PointList.h"

PointList::PointList()
{
    pl = new vector< Point* >();
}

/*PointList::PointList(Point *p)
{
    pl = new vector< Point* >();
    pl->push_back(p);
}
*/

void PointList::addPoint(Point *p)
{
    pl->push_back(p);
}

void PointList::removePoint(Point *p)
{
    for (vector<Point *>::iterator it = pl->begin(); it != pl->end(); ++ it)
    {
        if (*(*it) == *p)
        {
            pl->erase(it);
            return;
        }
    }
}
