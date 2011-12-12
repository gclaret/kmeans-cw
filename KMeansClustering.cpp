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

bool KMeansClustering::assignAllPointsToNearestCluster()
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
            current_dist = (*it)->euclideanDistance((*c)->getCentroid());
            if (current_dist < min_dist)
            {
                min_dist = current_dist;
                closest_cluster = (*c);
            }
        }

        // assign point to closest_cluster and test for convergance.
        closest_cluster->addPoint((*it));
        //std::cout << "Previous id = " << (*it)->getCluster() << " and the new id = " << closest_cluster->id << std::endl;
        if (closest_cluster->id != (*it)->getCluster())
        {
            convergance = false;
        }
        (*it)->setCluster(closest_cluster->id);
    }

    return convergance;
}

bool KMeansClustering::naiveStep(MyQGraphicsView *my_view)
{
    bool converged;
    converged = assignAllPointsToNearestCluster();
    std::cout << "Converged = " << converged <<std::endl;

    for (vector<Cluster *>::iterator it = clusters.begin(); it != clusters.end(); ++ it)
    {
        std::cout << "colouring cluster " << (*it)->id << std::endl;
        my_view->colourCluster(*it);
    }

    for (std::vector<Cluster *>::iterator it = clusters.begin(); it != clusters.end(); ++it)
    {
        (*it)->updateCentroid();
    }
    return converged;
}

// for this, perhaps we should implement some compgeom algorithm for fast allocation of points.
// perhaps we should build the voronoi diagram?
void KMeansClustering::naiveKMeans(MyQGraphicsView *my_view)
{
    bool convergance = false;
    // randomly initialize (done in init())
    int round = 0;

    while (!convergance)
    {
        convergance = assignAllPointsToNearestCluster();
        my_view->delayedColourClusters(clusters);

        std::cout << "Round " << round << " summary" << std::endl;
        for (std::vector<Cluster *>::iterator it = clusters.begin(); it != clusters.end(); ++it)
        {
            std::cout << "Cluster " <<  (*it)->id << " has " << (*it)->getNumberOfPoints() << " points." << std::endl;
        }

        // update centroids based on clusters [TODO]
        std::cout << "Should print AFTER colouring." << std::endl;
        for (std::vector<Cluster *>::iterator it = clusters.begin(); it != clusters.end(); ++it)
        {
            (*it)->updateCentroid();
        }
        round++;
    }
    std::cout << "Converged." << std::endl;
}

vector<Cluster *> KMeansClustering::getClusters() const
{
    return clusters;
}
