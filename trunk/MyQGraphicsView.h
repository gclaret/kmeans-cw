#ifndef MYQGRAPHICSVIEW_H
#define MYQGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QMouseEvent>
#include <QTimer>
#include "PointList.h"
#include "Cluster.h"

#include <CGAL/Voronoi_diagram_2.h>

// triangulation
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Kernel::Point_2 Point;

typedef CGAL::Delaunay_triangulation_2<Kernel> Delaunay;
typedef Delaunay::Vertex_handle Vertex_handle;

class MyQGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyQGraphicsView(QWidget *parent = 0);
    void drawPoint(Point *p, QColor color = QColor("black"), int size = 4);
    void colourCluster(Cluster *c);
    QGraphicsScene *getScene();
    void delayedColourClusters(std::vector<Cluster *> &clusters);
    void delaunayTriangulate(std::vector<Point *> pts);

signals:

public slots:
    void mousePressEvent(QMouseEvent *e);
    void colourClusters();

private:
    QGraphicsScene *scene;
    std::vector<Cluster *> cluster_state;

};

#endif // MYQGRAPHICSVIEW_H
