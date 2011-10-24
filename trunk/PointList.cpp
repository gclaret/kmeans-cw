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

bool PointList::instance_created = false;
PointList *PointList::instance = NULL;

PointList *PointList::getInstance()
{
    if (!instance_created)
    {
        instance = new PointList();
        instance_created = true;
        return instance;
    }
    else
    {
        return instance;
    }
}

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
