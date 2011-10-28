#include "KMeansClustering.h"

KMeansClustering::KMeansClustering(int _k, PointList *p)
{
    k = _k;
    point_list = p;

    init();
}

void KMeansClustering::init()
{
    QColor colours[10] = {QColor("cyan"), QColor("darkCyan"), QColor("red"),
                          QColor("darkRed"), QColor("magenta"), QColor("darkMagenta"),
                          QColor("green"), QColor("darkGreen"), QColor("yellow"),
                          QColor("blue")};
    // do nothing.
    for (int i = 0; i < k; i++)
    {
        Cluster *c = new Cluster(colours[i]);
        clusters.push_back(c);
    }
}

void KMeansClustering::NaiveKMeans()
{
    // randomly initialize (done in init())
    // assign pts to nearest centroid

    // update centroids based on clusters
}
