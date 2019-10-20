#ifndef LSH_HPP
#define LSH_HPP

#include <vector>
using std::vector;

#include "hashTable.hpp"

template <typename M>
struct info;

template<>
struct info<class Curve* >{
    int maxCurvePoints;
    int delta;
    double **displacement;
    vector <class Point*> *points;
};

template<>
struct info<class Point* >{};

template<class T>
class LSH
{
    int k;
    int w;
    int L;
    vector<T> *input;
    struct info<T> info;
    class HashTable< vector < pair < class Point*, unsigned int > > > *hashTables;

public:
    LSH(int, int, int, vector<T>*);
    LSH(int,int,int,int,int,vector<T>*);
    ~LSH();
    int getk();
    int getw();
    int getL();
    T approximateNN(T , double *);
    class Point *createVector(class Curve*,int);
};

#endif