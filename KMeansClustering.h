#ifndef KMEANSCLUSTERING_H
#define KMEANSCLUSTERING_H

#include <utility>
#include "PointList.h"
#include "Cluster.h"

class KMeansClustering
{
public:
    KMeansClustering(int _k, PointList *p);
    void init();



    int getK();

private:
    void NaiveKMeans();

    int k;
    PointList *point_list;
    PointList *centroids;
    vector<Cluster *> clusters;
};

#endif // KMEANSCLUSTERING_H
