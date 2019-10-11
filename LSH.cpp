#include <iostream>
#include <limits>

#include "point.hpp"
#include "manhattanDistance.hpp"
#include "hashTable.hpp"
#include "LSH.hpp"

using namespace std;

// Class used for the implementation of the LSH algorithm

LSH::LSH(int givenk, int givenL, int givenw, vector<class Point *> *points)
{
    k = givenk;
    L = givenL;
    w = givenw;

    inputPoints = points;
    int dim = inputPoints->at(0)->getSize();

    unsigned int hashtableSize = inputPoints->size() / 16;
    hashTables = new class HashTable[L];
    for (int i = 0; i < L; i++)
    {
        hashTables[i].initialize(hashtableSize, w, k, dim);
    }
    //insert the points to the hashtables
    for (int i = 0; i < L; i++)
    {
        for (int j = 0; j < inputPoints->size(); j++)
        {
            hashTables[i].insertPoint(inputPoints->at(j));
        }
    }
}

LSH::~LSH()
{
    delete[] hashTables;
}

int LSH::getk()
{
    return k;
}

int LSH::getL()
{
    return L;
}

int LSH::getw()
{
    return w;
}

class Point *LSH::approximateNN(class Point *query, unsigned int *dist)
{
    class Point *b = NULL;
    class Point *p = NULL;
    unsigned int manhattanD;
    unsigned int distance = numeric_limits<int>::max();
    vector<class Point *> neighbours;
    int count;

    for (int i = 0; i < L; i++)
    {
        neighbours = hashTables[i].getNeighbours(query);
        count = 0;

        for (int j = 0; j < neighbours.size(); j++)
        {
            count++;
            if (count > 3 * L)
                break;

            p = neighbours.at(j);
            manhattanD = manhattanDist(query, neighbours.at(j));

            if (manhattanD < distance)
            {
                b = p;
                distance = manhattanD;
            }
        }
    }
    *dist = distance;
    return b;
}