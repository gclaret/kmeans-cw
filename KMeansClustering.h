#ifndef KMEANSCLUSTERING_H
#define KMEANSCLUSTERING_H

#include <utility>
#include <iostream>
#include <QTimer>
#include "PointList.h"
#include "Cluster.h"
#include "MyQGraphicsView.h"

class KMeansClustering
{
public:
    KMeansClustering(int _k, PointList *p);
    void naiveKMeans(MyQGraphicsView *my_view);
    bool naiveStep(MyQGraphicsView *my_view);
    vector<Cluster *> getClusters() const;

    int getK();

private:
    void init();
    bool assignAllPointsToNearestCluster();

    int k;
    PointList *point_list;
    PointList *centroids;
    vector<Cluster *> clusters;

};

#endif // KMEANSCLUSTERING_H