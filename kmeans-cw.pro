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

QMAKE_CXXFLAGS += -std=c++0x

unix:!symbian|win32: LIBS += -L$$PWD/../Libraries/CGAL-3.9/bin/lib/Debug/ -lCGAL-vc100-mt-gd -CGAL_Core-vc100-mt-gd -CGAL_ImageIO-cv100-mt-gd

INCLUDEPATH += $$PWD/../Libraries/CGAL-3.9/include
DEPENDPATH += $$PWD/../Libraries/CGAL-3.9/include

INCLUDEPATH += C:/Projects/Libraries/boost_1_47
INCLUDEPATH += C:/Projects/Libraries/CGAL-3.9/bin/include

INCLUDEPATH += C:\Projects\Libraries\CGAL-3.9\include\CGAL\auto_link
