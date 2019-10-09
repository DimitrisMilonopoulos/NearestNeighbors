#ifndef LSH_HPP
#define LSH_HPP

#include <vector>
#include <string>
#include "point.hpp"
#include "hashTable.hpp"

using namespace std;

class LSH{

    int k;
    int w;
    int L;
    vector <class Point*>* inputPoints;
    class HashTable<class Point*>* hashTables;

public:
    LSH(int, vector <class Point*>*, int, int);
    ~LSH();
    int getk();
    int getw();
    int getL();
};

#endif