#include "KMeansClustering.h"

KMeansClustering::~KMeansClustering()
{
    clusters.clear();
}

KMeansClustering::KMeansClustering(int _k, PointList *p, int algorithm)
{
    k = _k;
    point_list = p;

    vector<float> distance_list;
    for (int l = 0; l < point_list->size(); l++)
    {
        distance_list.push_back(0);
    }

    QColor colours[30] = {QColor(255, 0, 0), QColor(0, 255, 255), QColor(0, 0, 255),
                          QColor(0, 255, 0), QColor(255, 255, 0), QColor(255, 0, 255),
                          QColor(0, 64, 128), QColor(64, 0, 128), QColor(64, 128, 0),
                          QColor(128, 64, 0),

                          QColor(128, 0, 64), QColor(214, 41, 41), QColor(232, 17, 45),
                          QColor(252, 191, 201), QColor(143, 239, 45), QColor(242, 206, 104),
                          QColor(107, 71, 21), QColor(255, 214, 145), QColor(249, 221, 22),
                          QColor(91, 119, 204),

                          QColor(137, 119, 186), QColor(114, 119, 186), QColor(114, 81, 188),
                          QColor(102, 86, 188), QColor(94, 104, 196), QColor(56, 25, 122),
                          QColor(79, 0, 147), QColor(73, 48, 173), QColor(181, 209, 232),
                          QColor(102, 137, 204)

                         };

    if (algorithm == KMEANS_PLUSPLUS)
    {

        // 1. first cluster is randomly assigned from point_list.
        int rand_val = round(rand() % point_list->size());
        Cluster *first = new Cluster(colours[0], 0, (*point_list)[rand_val]->getX(), (*point_list)[rand_val]->getY());
        clusters.push_back(first);

        for (int i = 1; i < _k; i++)
        {
            // 2. For each point, compute D(x), the distance between x and the nearest center that has already been chosen.
            computeDistanceList(distance_list);

            // 3. Choose one new data point at random as a new center,
            // using a weighted prob dist where a point x is chosen with prob proportional to D(x)^2
            vector<float> cdf;
            prepareCDF(distance_list, cdf);
            Point *centre = selectPoint(cdf);

            Cluster *next = new Cluster(colours[i], i, centre->getX(), centre->getY());
            clusters.push_back(next);
        }


    }
    else if (algorithm == KMEANS_SHARP)
    {
        int centres = 3*round(log(_k));
        int id = 0;
        // 1. first 3*log(k) clusters are indepdently/uniformly chosen from point list.
        for (int i = 0; i < centres; i++)
        {
            int rand_val = round(rand() % point_list->size());
            Cluster *c = new Cluster(colours[i], id, (*point_list)[rand_val]->getX(), (*point_list)[rand_val]->getY());
            clusters.push_back(c);
            id++;
        }

        for (int i = 1; i < _k; i++)
        {
            for (int j = 0; j < centres; j++)
            {
                // 2. For each point, compute D(x).
                computeDistanceList(distance_list);

                // 3. Choose new data points with weight prob dist.
                vector<float> cdf;
                prepareCDF(distance_list, cdf);
                Point *centre = selectPoint(cdf);

                Cluster *next = new Cluster(colours[id], id, centre->getX(), centre->getY());
                clusters.push_back(next);
                id++;
            }
        }
    }
    else
    {
        init();
    }
}

void KMeansClustering::computeDistanceList(vector<float> &distance_list)
{
    int j = 0;
    for (vector<Point *>::iterator it = point_list->begin(); it != point_list->end(); ++it)
    {
        float shortest_distance = 10000000;
        for (vector<Cluster *>::iterator it2 = clusters.begin(); it2 != clusters.end(); ++it2)
        {
            float dist = pow((*it2)->getCentroid()->euclideanDistance((*it)), 2);
            if (dist < shortest_distance)
            {
                shortest_distance = dist;
            }
        }
        distance_list[j] = shortest_distance;
        j++;
    }
}

void KMeansClustering::prepareCDF(vector<float> &distance_list, vector<float> &cdf)
{
    float sum = 0;
    int n = distance_list.size();
    for (int i = 0; i < n; i++)
    {
        cdf.push_back(0);
    }

    // creating cdf
    for (int i = 0; i < n; i++)
    {
        float weight = distance_list[i];
        sum += weight;
        cdf[i] = sum;
    }

    // normalize
    for (int i = 0; i < n; i++)
    {
        cdf[i] /= sum;
    }
}

Point *KMeansClustering::selectPoint(vector<float> &cdf)
{
    // generate a random #
    float rand_val = (float)rand()/(float)RAND_MAX;

    // now search in the cdf for lowest i such that rand_val < cdf[i]
    // i'm lazy, so this is a linear search right now.  Speed up later perhaps.

    int result = binarySearch(rand_val, cdf);
    /*
    int prev_i = 0;
    for (int i = 0; i < cdf.size(); i++)
    {
        if (rand_val < cdf[i])
        {
            Point *ret_val = new Point((*point_list)[prev_i]->getX(), (*point_list)[prev_i]->getY());
            return ret_val;
        }
        prev_i = i;
    }

    // if it got out of that for loop, the last point is the solution.
    Point *ret_val = new Point((*point_list)[point_list->size() - 1]->getX(), (*point_list)[point_list->size() - 1]->getY());
    return ret_val;*/
    Point *ret_val = new Point((*point_list)[result]->getX(), (*point_list)[result]->getY());
    return ret_val;
}

int KMeansClustering::binarySearch(float a, vector<float> &arr)
{
    int min = 0;
    int max = arr.size() - 1;
    int mid = 0;

    while (!(arr[mid] == a) && !(max - min < 1))
    {
        mid = floor((min + max)/2);
        if (a > arr[mid])
        {
            min = mid + 1;
        }
        else
        {
            max = mid - 1;
        }
    }
    return mid;
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
        if (closest_cluster->id != (*it)->getCluster())
        {
            convergance = false;
        }
        (*it)->setCluster(closest_cluster->id);
    }

    return convergance;
}

void KMeansClustering::removeClusters(MyQGraphicsView *my_view)
{
    if (!clusters.empty())
    {
        for (std::vector<Cluster *>::iterator it = clusters.begin(); it != clusters.end(); ++it)
        {

            my_view->drawCluster((*it), true);
        }
    }
}

bool KMeansClustering::naiveStep(MyQGraphicsView *my_view)
{
    bool converged;
    converged = assignAllPointsToNearestCluster();

    if (my_view != NULL)
    {
        for (vector<Cluster *>::iterator it = clusters.begin(); it != clusters.end(); ++ it)
        {
            my_view->colourCluster(*it);
        }
    }

    for (std::vector<Cluster *>::iterator it = clusters.begin(); it != clusters.end(); ++it)
    {
        if (my_view != NULL) {my_view->drawCluster((*it), true);} // could be set to null if testing.
        (*it)->updateCentroid();
        if (my_view != NULL) {my_view->drawCluster((*it));}
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

        for (std::vector<Cluster *>::iterator it = clusters.begin(); it != clusters.end(); ++it)
        {
            std::cout << "Cluster " <<  (*it)->id << " has " << (*it)->getNumberOfPoints() << " points." << std::endl;
        }

        // update centroids based on clusters
        for (std::vector<Cluster *>::iterator it = clusters.begin(); it != clusters.end(); ++it)
        {
            (*it)->updateCentroid();
        }
        round++;
    }
}

vector<Cluster *> KMeansClustering::getClusters() const
{
    return clusters;
}

int KMeansClustering::round(float a)
{
    return (a > 0.0) ? floor(a + 0.5) : ceil(a - 0.5);
}

double KMeansClustering::getCost()
{
    double cost = 0;
    for (vector<Point *>::iterator it = point_list->begin(); it != point_list->end(); ++it)
    {
        // find cluster for this point.
        for (vector<Cluster *>::iterator it2 = clusters.begin(); it2 != clusters.end(); ++it2)
        {
            if ((*it2)->id == (*it)->getCluster())
            {
                double dist = (*it2)->getCentroid()->euclideanDistance(*it);
                cost += abs(dist);//pow(dist, 2);
                break;
            }
        }
    }
    return cost;
}
