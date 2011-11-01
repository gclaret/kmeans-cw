#ifndef KMEANSCLUSTERING_H
#define KMEANSCLUSTERING_H

#include <utility>
#include <iostream>
#include "PointList.h"
#include "Cluster.h"

class KMeansClustering
{
public:
    KMeansClustering(int _k, PointList *p);
    void NaiveKMeans();
    vector<Cluster *> getClusters() const;



    int getK();

private:
    void init();

    int k;
    PointList *point_list;
    PointList *centroids;
    vector<Cluster *> clusters;
};

#endif // KMEANSCLUSTERING_H
