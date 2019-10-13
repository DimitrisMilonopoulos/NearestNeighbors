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

    double *a = new double[d];
    double *s = sVectors[functionNo];
    double m;

    a[0] = floor((x->getCoord()[0] - s[0]) / w);
    m = a[0];

    for (int i = 1; i < d; i++)
    {
        a[i] = floor((x->getCoord()[i] - s[i]) / w);

        if (a[i] > m)
            m = a[i];
    }

    m++; // m must be greater than the max ai

    unsigned int result = 0;
    unsigned int M = 32 / k;

    for (int i = 0; i < d; i++)
    {
        result += ((int)a[d - 1 - i] * (int)pow(m, (double)i)) % M;
    }

    delete[] a;

    return result;
}
