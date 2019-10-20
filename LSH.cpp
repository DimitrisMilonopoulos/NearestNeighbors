#include <iostream>
#include <limits>
#include <cstring>
#include <cmath>

#include "point.hpp"
#include "manhattanDistance.hpp"
#include "dynamicTimeWarping.hpp"
#include "hashTable.hpp"
#include "LSH.hpp"

using namespace std;

// Class used for the implementation of the LSH algorithm

template<>
class Point* LSH<class Curve* >::createVector(class Curve* curve,int hashtableNo){

    //create the coord vector
    double* coord = new double[info.maxCurvePoints];
    memset(coord,0,info.maxCurvePoints*sizeof(double));
    double temp1,temp2;
    //snap the curves onto the grid
    int pos = 0;
    for (int i = 0; i < curve->getSize(); i++)
    {
        temp1 = round((curve->getCoord()[i].first-info.displacement[hashtableNo][0])/info.delta);
        temp2 =round((curve->getCoord()[i].second-info.displacement[hashtableNo][1])/info.delta);
        if (i>0){
            if (coord[2*pos]!=temp1 ||coord[(2*pos)+1]!=temp2 ){
                pos++;
                coord[2*pos] = temp1;
                coord[(2*pos)+1]= temp2;
            }
        }
        else{
            coord[2*i] = temp1;
            coord[(2*i)+1]= temp2;
        }
        
    }
    class Point* newclassPoint = new class Point(curve->getID(),coord,info.maxCurvePoints,curve);
    return newclassPoint;
}

template<class T>
class Point* LSH<T>::createVector(class Curve*,int){
    return NULL;
}

template <>
LSH<class Curve*>::LSH(int k, int L, int w,  vector<class Curve*> *input, int minPoints, int maxPoints)
{
    this->k = k;
    cout << this->k << " " << k << endl;
    this->L = L;
    this->w = w;

    this->input = input;

    info.delta = 8*minPoints;
    info.maxCurvePoints = maxPoints*2;
    info.displacement = new double*[L];

    //initialize the tau vectors
    for (int i = 0; i < L; i++)
    {
        info.displacement[i] = new double[2];
    }

    //create the tau vectors
    random_device rd;
    mt19937 generator(rd());
    uniform_real_distribution<> dis(0.0, (double)w);
    info.points = new vector<class Point*>[L];

    unsigned int hashtableSize = input->size() / 8;
    hashTables = new class HashTable<vector < pair <class Point*, unsigned int> > >[L];

    for (int i = 0; i < L; i++)
    {
        hashTables[i].initialize(hashtableSize, w, this->k, info.maxCurvePoints, 0);

        //initialize the vector points
        for (int j = 0; j < 2; j++)
        {
            info.displacement[i][j] = dis(generator);
        } 
    }

    //produce the new points for the hashtables
    class Point* newpoint;
    for (int i = 0; i < input->size(); i++)
    {
        for (int j = 0; j < L; j++)
        {
            newpoint = createVector(input->at(i),j);
            info.points[j].push_back(newpoint); //add to vector for deletion
            hashTables[j].insertPoint(newpoint); //insert to hashtable
        }
        
    }
}

template <>
LSH<class Point*>::LSH(int k, int L, int w, vector<class Point*> *input)
{
    this->k = k;
    this->L = L;
    this->w = w;

    this->input = input;

    int dim = input->at(0)->getSize();

    unsigned int hashtableSize = input->size() / 8;
    hashTables = new class HashTable<vector < pair <class Point*, unsigned int> > >[L];
    for (int i = 0; i < L; i++)
    {
        hashTables[i].initialize(hashtableSize, w, k, dim, 0);
    }
    //insert the points to the hashtables
    for (int i = 0; i < L; i++)
    {
        for (int j = 0; j < input->size(); j++)
        {
            hashTables[i].insertPoint(input->at(j));
        }
    }
}

template <class T>
LSH<T>::LSH(int k, int L, int w, vector<T> *input)
{
    this->k = k;
    this->L = L;
    this->w = w;

    this->input = input;
}

template<>
LSH<class Curve*>::~LSH(){
    delete[] hashTables;

    //delete taf
    for (int i = 0; i < L; i++)
    {
        delete info.displacement[i];
        while (!input[i].empty())
    {
        delete input[i].back();
        input[i].pop_back();
    }
    }
    
    delete (input);

    delete []info.displacement;
    

}
template <class T>
LSH<T>::~LSH()
{
    delete[] hashTables;
}

template <class T>
int LSH<T>::getk()
{
    return k;
}

template <class T>
int LSH<T>::getL()
{
    return L;
}

template <class T>
int LSH<T>::getw()
{
    return w;
}

template <>
class Point *LSH<class Point*>::approximateNN(class Point *query, double *dist)
{
    class Point *b = NULL;
    class Point *p = NULL;
    double manhattanD;
    double distance = numeric_limits<double>::max();
    vector< pair <class Point *, unsigned int> > neighbours;
    int count;

    for (int i = 0; i < L; i++)
    {
        unsigned int amplifiedResult = 0;
        neighbours = hashTables[i].getNeighbours(query, &amplifiedResult);
        count = 0;

        for (int j = 0; j < neighbours.size(); j++)
        {
            if(amplifiedResult == neighbours.at(j).second)
            {
                count++;
                if (count > 10 * L)
                    break;

                p = neighbours.at(j).first;
                manhattanD = manhattanDist(query, p);

                if (manhattanD < distance)
                {
                    b = p;
                    distance = manhattanD;
                }
            }
        }
    }
    *dist = distance;
    return b;
}

template <>
class Curve *LSH<class Curve*>::approximateNN(class Curve *query, double *dist)
{
    class Point *b = NULL;
    class Point *p = NULL;
    double dtwDist;
    double distance = numeric_limits<double>::max();
    vector< pair <class Point *, unsigned int> > neighbours;
    int count;

    for (int i = 0; i < L; i++)
    {
        unsigned int amplifiedResult = 0;
        class Point* gridCurve = createVector(query, i);
        neighbours = hashTables[i].getNeighbours(gridCurve, &amplifiedResult);
        count = 0;

        for (int j = 0; j < neighbours.size(); j++)
        {
            if(amplifiedResult == neighbours.at(j).second)
            {
                count++;
                if (count > 30 * L)
                    break;

                p = neighbours.at(j).first;
                dtwDist = DTWDistance(query, p->getCurvePtr());

                if (dtwDist < distance)
                {
                    b = p;
                    distance = dtwDist;
                }
            }
        }
        delete gridCurve;
    }
    *dist = distance;
    return b->getCurvePtr();
}

template <class T>
T LSH<T>::approximateNN(T query, double *dist){}


template class LSH<class Curve*>;
template class LSH<class Point*>;