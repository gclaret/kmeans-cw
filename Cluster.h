#ifndef CLUSTER_H
#define CLUSTER_H

#include <vector>
#include <QGraphicsView>
#include "PointList.h"
class Cluster
{
public:
    Cluster(QColor c);

    Point *getCentroid();
    int getNumberOfPoints();
    void computeConvexHull();
    vector<Point *> getPoints();
    void addPoint(Point *p);
    void removePoint(Point *p);
    QColor getColour();
    void clearPoints();

private:
    void randomInit();

    Point *centroid;
    int number_of_points;
    vector<Point *> convex_hull;
    vector<Point *> points;
    QColor colour;
};

#endif // CLUSTER_H
