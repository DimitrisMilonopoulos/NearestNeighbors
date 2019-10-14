#ifndef LSH_HPP
#define LSH_HPP

#include <vector>
using std::vector;

class LSH
{
    int k;
    int w;
    int L;
    vector<class Point *> *inputPoints;
    class HashTable *hashTables;

public:
    LSH(int, int, int, vector<class Point *> *);
    ~LSH();
    int getk();
    int getw();
    int getL();
    class Point *approximateNN(class Point *, double *);
};

#endif