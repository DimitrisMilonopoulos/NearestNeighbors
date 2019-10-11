#include <iostream>

#include "point.hpp"
#include "hashTable.hpp"
#include "LSH.hpp"

using namespace std;

// Class used for the implementation of the LSH algorithm

LSH::LSH(int givenw, vector <class Point*>* points, int givenk = 3, int givenL = 5)
{

    k = givenk;
    L = givenL;
    w = givenw;
    
    inputPoints = points;
    int dim = inputPoints->at(0)->getSize();

    hashTables = new class HashTable[L];
    for(int i = 0; i < L; i++){
        hashTables[i] = HashTable(inputPoints->size(), w, k, dim);
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