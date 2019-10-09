#include "hashTable.hpp"

unsigned int manhattanDist(class Item * item1, class Item* item2){
    unsigned int distance = 0;
    unsigned int dimensions = item1->getSize();
    int* coord_1 = item1->getCoord();
    int* coord_2 = item2->getCoord(); 

    for (int i = 0; i < dimensions; i++)
    {
        distance += abs(coord_1[i]-coord_2[i]);
    }
    return distance;
}