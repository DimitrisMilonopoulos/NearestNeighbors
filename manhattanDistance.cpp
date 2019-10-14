#include <cmath>

#include "point.hpp"

using namespace std;

double manhattanDist(class Point *Point1, class Point *Point2)
{
    double distance = 0;
    unsigned int dimensions = Point1->getSize();
    double *coord_1 = Point1->getCoord();
    double *coord_2 = Point2->getCoord();

    for (int i = 0; i < dimensions; i++)
    {
        distance += abs(coord_1[i] - coord_2[i]);
    }
    return distance;
}