#include <iostream>
#include <cmath>
#include <random>
#include <cstdlib>

#include "point.hpp"
#include "hashTable.hpp"

using namespace std;

void HashTable::initialize(size_t size, int givenw, int givenk, int givendim)
{
    k = givenk;
    w = givenw;
    d = givendim;

    bucketSize = size;
    buckets = new vector< pair<class Point *, unsigned int> >[bucketSize];
    unsigned int temp = 32/k;
    M = 1;
    M = M<<temp;
    cout << "M is : "<<M<<endl;
    sVectors = new double *[k];
    for (int i = 0; i < k; i++)
    {
        sVectors[i] = new double[d];
    }
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, (double)w);
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < d; j++)
        {
            sVectors[i][j] = dis(gen);
        }
    }
    mArray = new unsigned int[d];
    unsigned int m = INT32_MAX - 4;
    for (int i = 0; i < d; i++)
    {
        mArray[i] = modular_expo(m,i,M);
    }
    
}

HashTable::HashTable()
{
}

HashTable::~HashTable()
{
    cout << "Deleting Hashtable!" << endl;

    delete[] buckets;
    for (int i = 0; i < k; i++)
    {
        delete[] sVectors[i];
    }
    delete[] sVectors;
    delete[] mArray;
}

int HashTable::insertPoint(class Point *point)
{
    unsigned int result = amplifiedHashFunctionPoint(point);
    pair <class Point*, unsigned int> PAIR = make_pair(point, result);
    unsigned int position = amplifiedHashFunctionPoint(point) % bucketSize;
    buckets[position].push_back(PAIR);

    return 0;
}

unsigned int HashTable::amplifiedHashFunctionPoint(class Point *x)
{

    int shiftAmount = 32 / k;
    unsigned int temp, result = 0;
    for (int i = 0; i < k; i++)
    {
        temp = hashFunctionPoint(x, i);
        temp = temp << shiftAmount * i; //prepare the 32/k binary digits for concatenation
        result += temp;
    }
    return result;
}

unsigned int HashTable::hashFunctionPoint(class Point *x, int functionNo)
{

    int *a = new int[d];
    double *s = sVectors[functionNo];
    unsigned int m = UINT32_MAX -4;

    // a[0] = floor((x->getCoord()[0] - s[0]) / w);
    // m = a[0];

    for (int i = 0; i < d; i++)
    {
        a[i] =(int)floor((x->getCoord()[i] - s[i]) / w);

        // if (a[i] > m)
        //     m = a[i];
    }

    // m++; // m must be greater than the max ai

    unsigned int result = 0;
    unsigned int step1;

    for (int i = 0; i < d; i++)
    {   
        step1 =(a[d-1-i]%M + M)%M;
        result +=(step1*mArray[i])% M;
    }
    result = result %M;
    delete[] a;

    return result;
}

unsigned int modular_expo(unsigned int base,unsigned int exponent, unsigned int modulus){
    if (modulus == 1)
        return 0;
    if (exponent == 0)
        if (modulus == 1)
            return 1;
        else 
            return 0;
    
    unsigned long long c = 1;
    for (unsigned int i = 1; i <= exponent; i++)
    {
        c = (c*base) % modulus;
    }
    return c;
}

