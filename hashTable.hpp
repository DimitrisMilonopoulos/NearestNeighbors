#ifndef _HASHTABLE_
#define _HASHTABLE_

#include <vector>
using std::vector;

class HashTable
{

    unsigned int bucketSize;
    int k;
    int w;
    int d;
    vector<class Point *> *buckets;
    double **sVectors;

public:
    HashTable();
    HashTable(size_t, int, int, int);
    ~HashTable();

    //hashfunction operations
    unsigned int amplifiedHashFunctionPoint(class Point *x);
    unsigned int hashFunctionPoint(class Point *x, int functionNo);
    int insertPoint(class Point *);
    int findPoint(class Point *);
    vector<class Point *> &getNeighbours(class Point *x)
    {
        unsigned int position = amplifiedHashFunctionPoint(x);
        return buckets[position];
    }
};

#endif