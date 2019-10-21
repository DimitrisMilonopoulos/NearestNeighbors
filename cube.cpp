#include <iostream>
#include <limits>
#include <bitset>

#include "dataStructs.hpp"
#include "manhattanDistance.hpp"
#include "hashTable.hpp"
#include "cube.hpp"

using namespace std;

// Class used for the implementation of the randomized projections on a hypercube algorithm

Cube::Cube(int givenk, int givenMaxPoints, int givenProbes, int givenw, vector<class Point *> *points)
{
    k = givenk;
    maxPoints = givenMaxPoints;
    probes = givenProbes;
    w = givenw;

    hyperCube = points;
    int dim = hyperCube->at(0)->getSize();

    unsigned int hashtableSize = hyperCube->size() / 8;
    hashTables = new class HashTable< map<unsigned int, char> >[k];

    for (int i = 0; i < k; i++)
    {
        hashTables[i].initialize(hashtableSize, w, k, dim,givenProbes);
    }
    
    //create a list of vectors where the points will be saved
    //calculate the size of the points
    unsigned int temp = 1;
    temp = temp << k;
    hyperCube = new vector<class Point *>[temp];

    unsigned int acme;
    //insert the points into the hypercube
    for (int i = 0; i < points->size(); i++)
    {
        acme = getAcme(points->at(i));
        hyperCube[acme].push_back(points->at(i));
    }
}


unsigned int Cube::getAcme(class Point *point)
{

    unsigned int acme = 0;
    unsigned int hashresult;
    for (int j = 0; j < k; j++)
    {
        hashresult = hashTables[j].insertPoint(point);
        hashresult = hashresult << j;   
        acme += hashresult;         
    }
    return acme;
}


Cube::~Cube()
{
    delete[] hashTables;
    delete [] hyperCube;
}


int Cube::getk()
{
    return k;
}


int Cube::getProbes()
{
    return probes;
}


int Cube::getw()
{
    return w;
}


int Cube::getMaxPoints()
{
    return maxPoints;
}


class Point *Cube::findNN(class Point *query, double *dist)
{
    class Point* p,* b = NULL;
    double manhattanD;
    double distance = numeric_limits<double>::max();
    int count;
    int probeCounter = 0;
    unsigned int acmeNo = getAcme(query);
    vector <class Point*> *acme = NULL;
    unsigned int mask = 1,pos;
    count = 0;
    vector <pair<unsigned int, unsigned int> > *neighborPos1,*neighborPos2;
    neighborPos1 =  new vector< pair<unsigned int, unsigned int> >;
    if (probes > k){
        probeCounter = k;
    }
    else{
        probeCounter = probes;
    }
    
    for (int i = 0; i < probeCounter; i++)
    {
        if (i==0){
            acme = &hyperCube[acmeNo];
            if(searchAcme(acme,query,&count,&distance,&b)){
                neighborPos1->clear();
                delete neighborPos1;
                *dist = distance;
                return b;

            }
        }
        else{
            if (i>1)
                mask = mask << 1;
            pos = acmeNo ^ mask;
            acme = &hyperCube[pos]; 
            if(searchAcme(acme,query,&count,&distance,&b)){
                neighborPos1->clear();
                delete neighborPos1;
                *dist = distance;
                return b;

            }
        neighborPos1->push_back(make_pair(pos,i));
        }

    }
    probeCounter = 1;
    int canProduce;
    int newPos;
    for (int i = 0; i < k-1; i++)
    {
        neighborPos2 =  new vector< pair<unsigned int, unsigned int> >;
        for (int j = 0 ; j <neighborPos1->size();j++){
            //try to produce the neighbors with hamming distance bigger by one
            canProduce = neighborPos1->at(j).second;
            mask = 1;
            mask = mask << (canProduce-1);
            for (int k = 0; k <canProduce; k++ ){
                pos = neighborPos1->at(j).first ^ mask;
                newPos = canProduce - k-1;
                if(searchAcme(acme,query,&count,&distance,&b) || (probeCounter == probes)){
                    neighborPos1->clear();
                    delete neighborPos1;
                    neighborPos2->clear();
                    delete neighborPos2;
                    *dist = distance;
                    return b;
                }
                neighborPos2->push_back(make_pair(pos,newPos));
                mask = mask >> 1;
                probeCounter++;
            }
            
        }
        // empty the first vector and fill it with the second
        neighborPos1->clear();
        delete neighborPos1;
        neighborPos1 = neighborPos2; 
    }

    *dist = distance;
    return b;
    
}


int Cube::searchAcme(vector <class Point*> * acme,class Point * query, int *count, double *distance, class Point**b){
    double manhattanD;
    class Point* p;
    for (int j = 0; j < acme->size(); j++)
        {
            *count = *count + 1;
            if (*count > maxPoints)
                return 1;

            p = acme->at(j);
            manhattanD = manhattanDist(query, p);

            if (manhattanD < *distance)
            {
                *b = p;
                *distance = manhattanD;
            }
        }
        return 0;
}