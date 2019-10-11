#include <iostream>
#include <fstream>
#include <sstream>

#include "point.hpp"

using namespace std;

//Class used to handle the input Points

Point::Point(string ID, int *coord, int siz)
{
    PointID = ID;
    coordinates = coord;
    size = siz;
}

Point::~Point()
{
    delete[] coordinates;
}

string Point::getID()
{
    return PointID;
}

int Point::getSize()
{
    return size;
}

int *Point::getCoord()
{
    return coordinates;
}