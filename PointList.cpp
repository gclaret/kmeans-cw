#include "PointList.h"

PointList::PointList()
{
    pl = new vector< Point* >();
}

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

void PointList::clear()
{
    pl->clear();
    //delete pl;
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

vector<Point *>::iterator PointList::begin()
{
    return pl->begin();
}

vector<Point *>::iterator PointList::end()
{
    return pl->end();
}

int PointList::size()
{
    return pl->size();
}

Point *PointList::operator[](unsigned int i) const
{
    Point *current;
    int j = 0;
    for (vector<Point *>::iterator it = pl->begin(); it != pl->end(); ++it)
    {
        current = (*it);
        if (j >= i)
        {
            return current;
        }
        j++;
    }
    return new Point(-1, -1);
}
