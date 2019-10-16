#ifndef CUBE_HPP
#define CUBE_HPP

#include "hashTable.hpp"
#include <vector>
using std::vector;
#include <map>
using std::map;

class Cube{
    int k;
    int maxPoints;
    int probes;
    int w;
    vector<class Point *> *hyperCube;
    class HashTable< map<unsigned int, char> > *hashTables;
    
    public:
    Cube(int, int, int, int, vector<class Point *> *);
    ~Cube();
    int getk();
    int getProbes();
    int getw();
    unsigned int getAcme(class Point *);
    int getMaxPoints();
    class Point *findNN(class Point *, double *);
    int searchAcme(vector <class Point*> *,class Point* query, int*,double*,class Point**);
};

#endif