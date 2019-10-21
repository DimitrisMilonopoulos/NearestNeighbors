#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <random>

#include "dataStructs.hpp"

using namespace std;

/////// POINTS //////

Point::Point(string ID, double *coord, int siz,class Curve *ptr)
{
    this->ID = ID;
    coordinates = coord;
    size = siz;
    curvePtr = ptr;
}


Point::~Point()
{
    delete[] coordinates;
}


string Point::getID()
{
    return ID;
}


int Point::getSize()
{
    return size;
}


double *Point::getCoord()
{
    return coordinates;
}


class Curve* Point::getCurvePtr()
{
    return curvePtr;
}


////// CURVES //////

Curve::Curve(string givenID,pair <double,double>* coords, int size){
    ID = givenID;
    coordinates = coords;
    this->size = size;
}


pair<double,double>* Curve::getCoord(){
    return coordinates;
}


int Curve::getSize(){
    return size;
}


Curve::~Curve(){
    delete coordinates;
}


string Curve::getID(){
    return ID;
}


////// GRID CURVES //////
template <class T>
gridCurve<T>::gridCurve(vector<class Curve*>* curves, int k, int L, int w, int probes, int minCurvePoints, int maxCurvePoints, string algorithm)
{
    this->curves = curves;
    this->k = k;
    this->L = L;
    this->w = w;
    this->probes = probes;
    this->minCurvePoints = minCurvePoints;
    this->maxCurvePoints = maxCurvePoints;

    this->algorithm = new class LSH();
    this->delta = 8*minCurvePoints;
    this->maxCurvePoints = maxCurvePoints*2;
    this->displacement = new double*[L];

    //initialize the tau vectors
    for (int i = 0; i < L; i++)
    {
        this->displacement[i] = new double[2];
    }

    //create the tau vectors
    random_device rd;
    mt19937 generator(rd());
    uniform_real_distribution<> dis(0.0, (double)w);
    this->points = new vector<class Point*>[L];

    if(algorithm == "LSH"){

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
    else if(algorithm == "Hypercube"){
        this->algorithm = new class cube();
    }
}

template<>
class Point* gridCurve<class Curve* >::createVector(class Curve* curve,int hashtableNo){

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