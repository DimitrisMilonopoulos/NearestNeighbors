#ifndef LSH_HPP
#define LSH_HPP

#include <vector>
#include <string>

using namespace std;

class LSH{

    int k;
    int w;
    int L;
    vector <class Point*>* inputPoints;
    class HashTable<class Point>* hashTables;

public:
    LSH(int, int, int, vector <class Point*>*);
    ~LSH();
    int getk();
    int getw();
    int getL();
};

#endif