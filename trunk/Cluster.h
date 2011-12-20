#ifndef CLUSTER_H
#define CLUSTER_H

#include <vector>
#include <QGraphicsView>
#include "PointList.h"
class Cluster
{
public:
    Cluster(QColor c, int id);
    Cluster(QColor c, int id, double _x, double _y);
    ~Cluster();

    Point *getCentroid();
    void updateCentroid();
    int getNumberOfPoints() const;
    vector<Point *> *getPoints() const;
    void addPoint(Point *p);
    void removePoint(Point *p);
    QColor getColour() const;
    void clearPoints();
    int id;

    friend ostream &operator<<(ostream &output, const Cluster &c);

    // add << operator that spits out all the points.  Need this for debugging.
private:
    void randomInit();

    Point *centroid;
    vector<Point *> *points;
    QColor colour;
};

#endif // CLUSTER_H
