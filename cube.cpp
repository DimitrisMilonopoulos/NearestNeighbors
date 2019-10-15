#include <iostream>
#include <limits>

#include "point.hpp"
#include "manhattanDistance.hpp"
#include "hashTable.hpp"
#include "cube.hpp"

using namespace std;

// Class used for the implementation of randomized projections in a hypercube algorithm

Cube::Cube(int givenk, int givenMaxPoints, int givenProbes, int givenw, vector<class Point *> *points)
{
    k = givenk;
    maxPoints = givenMaxPoints;
    probes = givenProbes;
    w = givenw;

    inputPoints = points;
    int dim = inputPoints->at(0)->getSize();

    unsigned int hashtableSize = inputPoints->size() / 8;
    hashTables = new class HashTable<char>[k];
    for (int i = 0; i < k; i++)
    {
        hashTables[i].initialize(hashtableSize, w, k, dim,givenProbes);
        hashTables[i].initBuck();
    }

    
    //create a list of vectors where the points will be saved
    //calculate the size of the points
    unsigned int temp = 1;
    temp = temp << k;
    inputPoints = new vector<class Point *>[temp];

    unsigned int bucket;
    //insert the points into the hypercube
    for (int i = 0; i < points->size(); i++)
    {
        bucket = getBucket(points->at(i));
        inputPoints[bucket].push_back(points->at(i));
    }
     
}

unsigned int Cube::getBucket(class Point *point){
    unsigned int bucket = 0;
    unsigned int hashresult;
    for (int j = 0; j < k; j++)
    {
            hashresult = hashTables[j].insertPoint(point);
            hashresult = hashresult << j;   
            bucket += hashresult;         
        }
    return bucket;
}
Cube::~Cube()
{
    delete[] hashTables;
}

int Cube::getk()
{
    return k;
}

int Cube::getProbes()
{
    return probes;
}

int Cube::getw()
{
    return w;
}

class Point *Cube::approximateNN(class Point *query, double *dist)
{
    class Point *b = NULL;
    class Point *p = NULL;
    double manhattanD;
    double distance = numeric_limits<double>::max();
    vector< pair <class Point *, unsigned int> > neighbours;
    int count;

    for (int i = 0; i < k; i++)
    {
        unsigned int amplifiedResult = 0;
        neighbours = hashTables[i].getNeighbours(query, &amplifiedResult);
        count = 0;

        for (int j = 0; j < neighbours.size(); j++)
        {
            if(amplifiedResult == neighbours.at(j).second)
            {
                count++;
                if (count > maxPoints)
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