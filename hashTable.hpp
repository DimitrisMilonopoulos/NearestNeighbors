#ifndef _HASHTABLE_
#define _HASHTABLE_

#include <cstdlib>
#include <vector>

#include "point.hpp"

unsigned int manhattanDist(class Point*, class Point*);

template <class T>
class HashTable{

    unsigned int bucketSize;
    int k;
    int w;
    int d;
    vector<T*>* buckets;
    double** sVectors;

    
    public:

    HashTable();
    HashTable(size_t, int, int, int);
    ~HashTable();

    //hashfunction operations
    unsigned int amplifiedHashFunctionPoint(class Point*);
    unsigned int hashFunctionPoint(T x, int functionNo);
    int insertPoint(T*);
    int findPoint(T*);
};

#endif