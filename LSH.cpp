#include <iostream>

#include "point.hpp"
#include "hashTable.hpp"
#include "LSH.hpp"

using namespace std;

// Class used for the implementation of the LSH algorithm

LSH::LSH(int givenk = 3, int givenL = 5, int givenw, vector <class Point*>* points)
{

    k = givenk;
    L = givenL;
    w = givenw;
    inputPoints = points;
    hashTables = new class HashTable<class Point>[L];
    for(int i = 0; i < L; i++){
        hashTables[i] = HashTable<class Point>(inputPoints->size());
    }
}

LSH::~LSH()
{
    delete [] hashTables;
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