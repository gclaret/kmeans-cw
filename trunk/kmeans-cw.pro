#-------------------------------------------------
#
# Project created by QtCreator 2011-10-17T18:54:14
#
#-------------------------------------------------

QT       += core gui

TARGET = kmeans-cw
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    point.cpp \
    PointList.cpp \
    MyQGraphicsView.cpp \
    KMeansClustering.cpp \
    Cluster.cpp

HEADERS  += mainwindow.h \
    Point.h \
    PointList.h \
    MyQGraphicsView.h \
    KMeansClustering.h \
    Cluster.h

FORMS    += mainwindow.ui

