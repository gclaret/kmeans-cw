#ifndef KMEANSCLUSTERING_H
#define KMEANSCLUSTERING_H

#include <utility>
#include <iostream>
#include <QTimer>
#include "PointList.h"
#include "Cluster.h"
#include "MyQGraphicsView.h"
#include <math.h>

#define KMEANS 0
#define KMEANS_PLUSPLUS 1
#define KMEANS_SHARP 2

class KMeansClustering
{
public:
    KMeansClustering(int _k, PointList *p, int algorithm);
    ~KMeansClustering();
    void naiveKMeans(MyQGraphicsView *my_view);
    bool naiveStep(MyQGraphicsView *my_view = NULL);
    vector<Cluster *> getClusters() const;
    void removeClusters(MyQGraphicsView *my_view);
    double getCost();

    int getK();

private:
    void init();
    bool assignAllPointsToNearestCluster();
    void computeDistanceList(vector<float> &distance_list);
    void prepareCDF(vector<float> &distance_list, vector<float> &cdf);
    Point *selectPoint(vector<float> &cdf);
    int round(float a);
    int binarySearch(float a, vector<float> &arr);

    int k;
    PointList *point_list;
    vector<Cluster *> clusters;

};

#endif // KMEANSCLUSTERING_H
