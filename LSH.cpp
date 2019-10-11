#include <iostream>

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

    hashTables = new class HashTable[L];
    for (int i = 0; i < L; i++)
    {
        hashTables[i] = HashTable(inputPoints->size(), w, k, dim);
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