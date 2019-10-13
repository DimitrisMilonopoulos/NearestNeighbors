#ifndef _HASHTABLE_
#define _HASHTABLE_

#include <vector>
using std::vector;
#include <utility>
using std::pair;

class HashTable
{

    unsigned int bucketSize;
    int k;
    int w;
    int d;
    vector< pair<class Point *, unsigned int> > *buckets;
    double **sVectors;
    unsigned int * mArray;

public:
    HashTable();
    void initialize(size_t, int, int, int);
    ~HashTable();

    //hashfunction operations
    unsigned int amplifiedHashFunctionPoint(class Point *x);
    unsigned int hashFunctionPoint(class Point *x, int functionNo);
    int insertPoint(class Point *);
    int findPoint(class Point *);
    vector< pair<class Point *, unsigned int> > &getNeighbours(class Point *x, unsigned int* amplifiedResult)
    {
        *amplifiedResult = amplifiedHashFunctionPoint(x);
        return buckets[*amplifiedResult % bucketSize];
    }
};

unsigned int modular_expo(unsigned int base,unsigned int exponent, unsigned int modulus);

#endif