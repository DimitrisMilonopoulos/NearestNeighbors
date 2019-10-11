#include <cmath>

#include "point.hpp"

using namespace std;

unsigned int manhattanDist(class Point *Point1, class Point *Point2)
{
    unsigned int distance = 0;
    unsigned int dimensions = Point1->getSize();
    int *coord_1 = Point1->getCoord();
    int *coord_2 = Point2->getCoord();

    for (int i = 0; i < dimensions; i++)
    {
        distance += abs(coord_1[i] - coord_2[i]);
    }
    return distance;
}