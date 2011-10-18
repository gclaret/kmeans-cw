#ifndef POINT_H
#define POINT_H

class Point
{
public:
    Point();
    Point(int x, int y);

    int getX();
    int getY();
    void setX(int x);
    void setY(int y);

    bool operator==(const Point &p) const;
private:
    int x;
    int y;
};

#endif // POINT_H
