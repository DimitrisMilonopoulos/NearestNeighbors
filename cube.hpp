#ifndef CUBE_HPP
#define CUBE_HPP

#include "hashTable.hpp"
#include <vector>
using std::vector;

class Cube{
    int k;
    int maxPoints;
    int probes;
    int w;
    vector<class Point *> *inputPoints;
    class HashTable<char> *hashTables;
    
    public:
    Cube(int, int, int, int, vector<class Point *> *);
    ~Cube();
    int getk();
    int getProbes();
    int getw();
    class Point *approximateNN(class Point *, double *);
};

#endif