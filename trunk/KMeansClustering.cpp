#include "KMeansClustering.h"

KMeansClustering::KMeansClustering(int _k, PointList *p)
{
    k = _k;
    point_list = p;

    init();
}

void KMeansClustering::init()
{
    QColor colours[10] = {QColor("cyan"), QColor("magenta"), QColor("red"),
                          QColor("darkRed"), QColor("darkCyan"), QColor("darkMagenta"),
                          QColor("green"), QColor("darkGreen"), QColor("yellow"),
                          QColor("blue")};
    // do nothing.
    for (int i = 0; i < k; i++)
    {
        Cluster *c = new Cluster(colours[i], i);
        clusters.push_back(c);
    }
}

bool KMeansCluster::assignAllPointsToNearestCluster()
{
    bool convergance = true;

    for (vector<Point *>::iterator it = point_list->begin(); it != point_list->end(); ++it)
    {
        Cluster *closest_cluster = clusters.at(0);
        double min_dist, current_dist = 0.0;

        // find the cluster with closest centroid, by euclidean distance
        min_dist = (*it)->euclideanDistance(closest_cluster->getCentroid());
        for (vector<Cluster *>::iterator c = clusters.begin(); c != clusters.end(); ++c)
        {
            //std::cout << "This cluster is " << current_dist << " from the point " << *(*it) << std::endl;
            current_dist = (*it)->euclideanDistance((*c)->getCentroid());
            if (current_dist < min_dist)
            {
                //std::cout << "New closest centroid." << std::endl;
                min_dist = current_dist;
                closest_cluster = (*c);
            }
            //std::cout << "Current closest cluster centered at " << *(closest_cluster->getCentroid()) << std::endl;
        }

        // assign point to closest_cluster and test for convergance.
        closest_cluster->addPoint((*it));
        std::cout << "Previous id = " << (*it)->getCluster() << " and the new id = " << closest_cluster->id << std::endl;
        if (closest_cluster->id != (*it)->getCluster())
        {
            convergance = false;
        }
        (*it)->setCluster(closest_cluster->id);
    }

    return convergance;
}

// for this, perhaps we should implement some compgeom algorithm for fast allocation of points.
// perhaps we should build the voronoi diagram?
void KMeansClustering::NaiveKMeans()
{
    bool convergance = false;
    // randomly initialize (done in init())

    while (!convergance)
    {
        convergance = assignAllPointsToNearestCluster();
        // update centroids based on clusters [TODO]
    }
}

vector<Cluster *> KMeansClustering::getClusters() const
{
    return clusters;
}
