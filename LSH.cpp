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

    unsigned int hashtableSize = inputPoints->size() / 8;
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

class Point *LSH::approximateNN(class Point *query, double *dist)
{
    class Point *b = NULL;
    class Point *p = NULL;
    double manhattanD;
    double distance = numeric_limits<double>::max();
    vector< pair <class Point *, unsigned int> > neighbours;
    int count;

    for (int i = 0; i < L; i++)
    {
        unsigned int amplifiedResult = 0;
        neighbours = hashTables[i].getNeighbours(query, &amplifiedResult);
        count = 0;

        for (int j = 0; j < neighbours.size(); j++)
        {
            if(amplifiedResult == neighbours.at(j).second)
            {
                count++;
                if (count > 10 * L)
                    break;

                p = neighbours.at(j).first;
                manhattanD = manhattanDist(query, p);

                if (manhattanD < distance)
                {
                    b = p;
                    distance = manhattanD;
                }
            }
        }
    }
    *dist = distance;
    return b;
}