#include <iostream>
#include <cmath>
#include <random>
#include <cstring>
#include <cstdlib>
#include <utility>

#include "point.hpp"
#include "hashTable.hpp"

using namespace std;

template <class T>
void HashTable<T>::initialize(size_t size, int givenw, int givenNumFunct, int givendim, int givenMaxPoints)
{
    numFunct = givenNumFunct;
    w = givenw;
    dimensions = givendim;
    maxPoints = givenMaxPoints;

    // create buckets

    bucketSize = size;
    buckets = new T[bucketSize];

    // initialize M

    unsigned int temp = 32/numFunct;
    M = 1;
    M = M<<temp;

    // create si arrays (fill with uniformly random numbers from 0 to w)

    sVectors = new double *[numFunct];
    for (int i = 0; i < numFunct; i++)
    {
        sVectors[i] = new double[dimensions];
    }

    uniform_real_distribution<> dis(0.0, (double)w);

    for (int i = 0; i < numFunct; i++)
    {
        for (int j = 0; j < dimensions; j++)
        {
            sVectors[i][j] = dis(generator);
        }
    }

    // create array to keep powers of m

    mArray = new unsigned int[dimensions];
    unsigned int m = INT32_MAX - 4;
    for (int i = 0; i < dimensions; i++)
    {
        mArray[i] = modular_expo(m,i,M);
    }

}

template <class T>
HashTable<T>::HashTable(): generator((std::random_device())())
{
}

template <class T>
HashTable<T>::~HashTable()
{
    cout << "Deleting Hashtable!" << endl;

    delete[] buckets;
    for (int i = 0; i < numFunct; i++)
    {
        delete[] sVectors[i];
    }
    delete[] sVectors;
    delete[] mArray;
}
template <>
int HashTable<vector < pair <class Point*, unsigned int> > >::insertPoint(class Point *point)
{
    unsigned int result = amplifiedHashFunctionPoint(point);
    pair <class Point*, unsigned int> PAIR = make_pair(point, result);
    unsigned int position = result % bucketSize;
    buckets[position].push_back(PAIR);

    return 0;
}

template <>
int HashTable<char>::insertPoint(class Point *point)
{
    unsigned int result = amplifiedHashFunctionPoint(point);
    unsigned int position = result % bucketSize;

    char* temp = &buckets[position];

    if(*temp == -1){
        uniform_int_distribution<> dis(0, 1);
        *temp = dis(generator);
    }

    return *temp;
}

template <class T>
int HashTable<T>::insertPoint(class Point *point)
{
    return 0;
};

template <class T>
unsigned int HashTable<T>::amplifiedHashFunctionPoint(class Point *x)
{

    int shiftAmount = 32 / numFunct;
    unsigned int temp, result = 0;
    for (int i = 0; i < numFunct; i++)
    {
        temp = hashFunctionPoint(x, i);
        temp = temp << shiftAmount * i; //prepare the 32/numFunct binary digits for concatenation
        result += temp;
    }
    return result;
}

template <class T>
unsigned int HashTable<T>::hashFunctionPoint(class Point *x, int functionNo)
{

    int *a = new int[dimensions];
    double *s = sVectors[functionNo];
    unsigned int m = UINT32_MAX -4;

    // a[0] = floor((x->getCoord()[0] - s[0]) / w);
    // m = a[0];

    for (int i = 0; i < dimensions; i++)
    {
        a[i] =(int)floor((x->getCoord()[i] - s[i]) / w);

        // if (a[i] > m)
        //     m = a[i];
    }

    // m++; // m must be greater than the max ai

    unsigned int result = 0;
    unsigned int step1;

    for (int i = 0; i < dimensions; i++)
    {   
        step1 =(a[dimensions-1-i]% M + M)%M;
        result +=(step1*mArray[i])% M;
    }
    result = result % M;
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

template class HashTable<vector < pair <class Point*, unsigned int> > >;
template class HashTable<char>;