#ifndef LSH_HPP
#define LSH_HPP

#include <vector>
using std::vector;

#include "hashTable.hpp"

class LSH
{
    int k;
    int w;
    int L;
    vector<class Point *> *inputPoints;
    class HashTable< vector < pair < class Point*, unsigned int > > > *hashTables;

public:
    LSH(int, int, int, vector<class Point *> *);
    ~LSH();
    int getk();
    int getw();
    int getL();
    class Point *approximateNN(class Point *, double *);
};

#endif