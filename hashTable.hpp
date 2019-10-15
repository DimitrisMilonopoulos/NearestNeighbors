#ifndef _HASHTABLE_
#define _HASHTABLE_

#include <vector>
using std::vector;
#include <utility>
using std::pair;

template <class T>
class HashTable
{

    unsigned int bucketSize;
    int numFunct;
    int w;
    int dimensions;
    int maxPoints;
    unsigned int M;
    T *buckets;
    double **sVectors;
    unsigned int * mArray;

public:
    HashTable();
    void initialize(size_t, int, int, int, int);
    ~HashTable();

    //hashfunction operations
    unsigned int amplifiedHashFunctionPoint(class Point *x);
    unsigned int hashFunctionPoint(class Point *x, int functionNo);
    int insertPoint(class Point *);
    int findPoint(class Point *);
    void initBuck(){
        memset(T,-1,bucketSize*sizeof(T));
    }
    vector< pair<class Point *, unsigned int> > &getNeighbours(class Point *x, unsigned int* amplifiedResult)
    {
        *amplifiedResult = amplifiedHashFunctionPoint(x);
        return buckets[*amplifiedResult % bucketSize];
    }
    T getDigit(class Point* x, unsigned int* amplifiedResult){
        *amplifiedResult = amplifiedHashFunctionPoint(x);
        return buckets[*amplifiedResult % bucketSize];
    }
};

unsigned int modular_expo(unsigned int base,unsigned int exponent, unsigned int modulus);

#endif