#ifndef POINT_HPP
#define POINT_HPP

#include <string>
using std::string;

class Point
{
    string PointID;
    int *coordinates;
    int size;

public:
    Point();
    Point(string ID, int *coord, int siz);
    ~Point();
    string getID();
    int *getCoord();
    int getSize();
};

#endif