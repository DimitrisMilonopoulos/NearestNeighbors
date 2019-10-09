#ifndef _HASHTABLE_
#define _HASHTABLE_

#include "fileReading.hpp"
#include <cstdlib>
#include <vector>

unsigned int manhattanDist(class Point *, class Point*);

template <typename T>
class HashTable{
    unsigned int bucketSize;
    vector<T*> *buckets;
    
    public:
    HashTable();
    HashTable(unsigned int size);
    ~HashTable();

    //hashfunction operations
    int insertPoint(T*,unsigned int position);
    int findPoint(T*);
};

#endif