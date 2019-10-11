#ifndef _HASHTABLE_
#define _HASHTABLE_

#include <cstdlib>
#include <vector>

#include "point.hpp"

unsigned int manhattanDist(class Point*, class Point*);

class HashTable{

    unsigned int bucketSize;
    int k;
    int w;
    int d;
    vector<class Point*>* buckets;
    double** sVectors;

    
    public:

    HashTable();
    HashTable(size_t, int, int, int);
    ~HashTable();

    //hashfunction operations
    unsigned int amplifiedHashFunctionPoint(class Point* x);
    unsigned int hashFunctionPoint(class Point* x, int functionNo);
    int insertPoint(class Point*);
    int findPoint(class Point*);
};




#endif