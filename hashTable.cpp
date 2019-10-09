#include <iostream>
#include <vector>
#include <string>

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

template <typename T>
HashTable<T>::HashTable(unsigned int size){
    bucketSize = size;
    buckets = new vector<T*>[bucketSize];
}

template <typename T>
HashTable<T>::~HashTable(){
    delete []buckets;
}

template <typename T>
int HashTable<T>::insertPoint(T* Point,unsigned int position){
    if (position>=bucketSize){
        cout << "Invalid hash table position"<<endl;
        return 1;
    }
    buckets[position].push_back(Point);
}