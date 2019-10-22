#include <iostream>
#include <limits>
#include <cstring>
#include <cmath>

#include "dataStructs.hpp"
#include "manhattanDistance.hpp"
#include "dynamicTimeWarping.hpp"
#include "hashTable.hpp"
#include "LSH.hpp"

using namespace std;

// Class used for the implementation of the LSH algorithm
template <class T>
LSH<T>::LSH(int k, int L, int w, vector<class Point*> *input)
{
    this->k = k;
    this->L = L;
    this->w = w;

    this->input = input;

    int dim = input->at(0)->getSize();

    unsigned int hashtableSize = input->size() / 8;
    hashTables = new class HashTable<vector < pair <class Point*, unsigned int> > >[L];
    for (int i = 0; i < L; i++)
    {
        hashTables[i].initialize(hashtableSize, w, k, dim, 0);
    }
    //insert the points to the hashtables
    for (int i = 0; i < L; i++)
    {
        for (int j = 0; j < input->size(); j++)
        {
            hashTables[i].insertPoint(input->at(j));
        }
    }
}


template<>
LSH<class Curve*>::~LSH()
{
    delete[] hashTables;
}

template <class T>
LSH<T>::~LSH()
{
    delete[] hashTables;
}


template <class T>
int LSH<T>::getk()
{
    return k;
}


template <class T>
int LSH<T>::getL()
{
    return L;
}


template <class T>
int LSH<T>::getw()
{
    return w;
}


template <>
class Point *LSH<class Point*>::approximateNN(class Point *query, double *dist)
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


template <>
class Curve *LSH<class Curve*>::approximateNN(class Point *query, double *dist)
{
    class Point *b = NULL;
    class Point *p = NULL;
    double dtwDist;
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
                if (count > 30 * L)
                    break;

                p = neighbours.at(j).first;
                dtwDist = DTWDistance(query->getCurvePtr(), p->getCurvePtr());

                if (dtwDist < distance)
                {
                    b = p;
                    distance = dtwDist;
                }
            }
        }
    }
    *dist = distance;
    return b->getCurvePtr();
}


template <class T>
T LSH<T>::approximateNN(class Point* query, double *dist){}


template class LSH<class Curve*>;
template class LSH<class Point*>;