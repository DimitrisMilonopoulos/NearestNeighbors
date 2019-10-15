#include <iostream>
#include <limits>
#include <bitset>

#include "point.hpp"
#include "manhattanDistance.hpp"
#include "hashTable.hpp"
#include "cube.hpp"

using namespace std;

// Class used for the implementation of the randomized projections on a hypercube algorithm

Cube::Cube(int givenk, int givenMaxPoints, int givenProbes, int givenw, vector<class Point *> *points)
{
    k = givenk;
    maxPoints = givenMaxPoints;
    probes = givenProbes;
    w = givenw;

    hyperCube = points;
    int dim = hyperCube->at(0)->getSize();

    unsigned int hashtableSize = hyperCube->size() / 8;
    hashTables = new class HashTable< map<unsigned int, char> >[k];

    for (int i = 0; i < k; i++)
    {
        hashTables[i].initialize(hashtableSize, w, k, dim,givenProbes);
    }
    
    //create a list of vectors where the points will be saved
    //calculate the size of the points
    unsigned int temp = 1;
    temp = temp << k;
    hyperCube = new vector<class Point *>[temp];

    unsigned int acme;
    //insert the points into the hypercube
    for (int i = 0; i < points->size(); i++)
    {
        acme = getAcme(points->at(i));
        hyperCube[acme].push_back(points->at(i));
    }
}

unsigned int Cube::getAcme(class Point *point){

    unsigned int acme = 0;
    unsigned int hashresult;
    for (int j = 0; j < k; j++)
    {
        hashresult = hashTables[j].insertPoint(point);
        hashresult = hashresult << j;   
        acme += hashresult;         
    }
    return acme;
}

Cube::~Cube()
{
    delete[] hashTables;
    delete [] hyperCube;
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

int Cube::getMaxPoints()
{
    return maxPoints;
}

class Point *Cube::findNN(class Point *query, double *dist)
{
    class Point* p,* b = NULL;
    double manhattanD;
    double distance = numeric_limits<double>::max();
    int count;

    unsigned int acmeNo = getAcme(query);
    vector <class Point*> *acme;
    unsigned int mask = 1;

    for (int i = 0; i < probes; i++)
    {
        if (i==0)
            acme = &hyperCube[acmeNo];
        else{
            if (i>1)
                mask = mask << 1;
            acme = &hyperCube[acmeNo ^ mask];       
        }

        count = 0;

        for (int j = 0; j < acme->size(); j++)
        {
            count++;
            if (count > maxPoints)
                break;

            p = acme->at(j);
            manhattanD = manhattanDist(query, p);

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