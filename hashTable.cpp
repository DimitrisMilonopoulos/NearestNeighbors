#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <random>

#include "point.hpp"
#include "hashTable.hpp"

using namespace std;




unsigned int manhattanDist(class Point * Point1, class Point* Point2){
    unsigned int distance = 0;
    unsigned int dimensions = Point1->getSize();
    int* coord_1 = Point1->getCoord();
    int* coord_2 = Point2->getCoord(); 

    for (int i = 0; i < dimensions; i++)
    {
        distance += abs(coord_1[i]-coord_2[i]);
    }
    return distance;
}

HashTable::HashTable(size_t size, int givenw, int givenk, int givendim){
    k = givenk;
    w = givenw;
    d = givendim;
    
    bucketSize = size;
    buckets = new vector<class Point*>[bucketSize];
    
    sVectors = new double*[k];
    for(int i = 0; i < k; i++){
        sVectors[i] = new double[d];
    }
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, (double)w);
    for(int i = 0; i < k; i++)
    {
        for (int j = 0; j < d; j++)
        {
            sVectors[i][j] = dis(gen);
        }
        
    }
}


HashTable::HashTable(){
}

HashTable::~HashTable(){
    delete []buckets;
}

int HashTable::insertPoint(class Point* point){
    unsigned int position = amplifiedHashFunctionPoint(point)%bucketSize;
    buckets[position].push_back(point);

    return 0;
}





unsigned int HashTable::amplifiedHashFunctionPoint(class Point* x){
    
    int shiftAmount = 32/k;
    unsigned int temp, result = 0;
    for (int i = 0; i < k; i++)
    {
        temp = hashFunctionPoint(x,i);
        temp = temp << shiftAmount*i; //prepare the 32/k binary digits for concatenation
        result += temp;
    }
    
    return result;
}



unsigned int HashTable::hashFunctionPoint(class Point* x, int functionNo){

    double* a = new double[d];
    double* s = sVectors[functionNo];
    double m;

    a[0] = floor((x->getCoord()[0] - s[0]) / w);
    m = a[0];

    for(int i = 1; i < d; i++)
    {
        a[i] = floor((x->getCoord()[i] - s[i]) / w);

        if(a[i] > m)
            m = a[i];
    }

    m++; // m must be greater than the max ai

    unsigned int result = 0;
    unsigned int M = 32/k;

    for(int i = 0; i < d; i++)
    {
        result += ((int) a[d-1-i] * (int) pow(m, (double)i)) % M;
    }

    return result;
}

