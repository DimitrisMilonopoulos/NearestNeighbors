#ifndef POINT_HPP
#define POINT_HPP

#include <string>
using std::string;

class Point
{
    string PointID;
    double *coordinates;
    int size;

public:
    Point();
    Point(string ID, double *coord, int siz);
    ~Point();
    string getID();
    double *getCoord();
    int getSize();
};

#endif