#ifndef _HASHTABLE_
#define _HASHTABLE_

#include <cstdlib>
#include <vector>

#include "point.hpp"

unsigned int manhattanDist(class Point *, class Point*);

template <class T>

class HashTable{
    unsigned int bucketSize;
    vector<T*> *buckets;
    
    public:
    HashTable();
    HashTable(size_t);
    ~HashTable();

    //hashfunction operations
    int insertPoint(T*,unsigned int);
    int findPoint(T*);
};

#endif