#ifndef _HASHTABLE_
#define _HASHTABLE_

#include "fileReading.hpp"
#include <cstdlib>
#include <vector>

unsigned int manhattanDist(class Item *, class Item*);

class HashTable{
    unsigned int bucketSize;
    vector<class Item*> *buckets;
    
    public:
    HashTable();
    HashTable(unsigned int size);
    ~HashTable();

    //hashfunction operations
    int insertItem(class Item*,unsigned int position);
    int findItem(class Item*);
};

#endif