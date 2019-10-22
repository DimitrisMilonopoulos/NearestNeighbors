#include <string>
#include <cmath>
#include <random>

#include "dataStructs.hpp"
#include "gridCurve.hpp"
#include "LSH.hpp"
#include "cube.hpp"

using namespace std;
////// GRID CURVES //////

template<class T>
gridCurve<T>::gridCurve(vector<class Curve*>* curves, int k, int L, int w, int probes, int minCurvePoints, int maxCurvePoints)
{   
    this->curves = curves;
    this->k = k;
    this->L = L;
    this->w = w;
    this->probes = probes;
    this->minCurvePoints = minCurvePoints;
    this->maxCurvePoints = maxCurvePoints;

    this->delta = 8*minCurvePoints;   /// this needs to change
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
    uniform_real_distribution<> dis(0.0, (double)this->delta);
    
    this->points = new vector<class Point*>*[L];

    for(int i = 0; i < L; i++){
        points[i] = new vector<class Point*>;
        points[i]->reserve(curves->size());
    }

    for(int i = 0; i < this->L; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            this->displacement[i][j] = dis(generator);
        }

        for(int t = 0; t < curves->size(); t++)
        {
            points[i]->push_back(createVector(curves->at(t), i));
        }
    }
}

template<>
int gridCurve<class LSH<class Curve*> >::initializeAlgorithm()
{
        
    this->algorithm = new class LSH<class Curve*>*[L];

    for(int i = 0; i < L; i++){
        this->algorithm[i] = new class LSH<class Curve*>(this->k, 1, this->w, points[i]);
    }

    return 0;
}

template<>
int gridCurve<class Cube<class Curve*> >::initializeAlgorithm()
{
        
    this->algorithm = new class Cube<class Curve*>*[L];

    for(int i = 0; i < L; i++){
        this->algorithm[i] = new class Cube<class Curve*>(this->k, maxCurvePoints, this->probes, this->w, points[i]);
    }

    return 0;
}

template <class T>
int gridCurve<T>::initializeAlgorithm(){return 0;}


template<class T>
class Point* gridCurve<T>::gridCurve::createVector(class Curve* curve, int gridNo){

    //create the coord vector
    double* coord = new double[this->maxCurvePoints];
    memset(coord,0,this->maxCurvePoints*sizeof(double));
    double temp1,temp2;

    //snap the curves onto the grid
    int pos = 0;
    for (int i = 0; i < curve->getSize(); i++)
    {
        temp1 = round( ( curve->getCoord()[i].first - this->displacement[gridNo][0] )/ this->delta );
        temp2 =round( ( curve->getCoord()[i].second - this->displacement[gridNo][1]) / this->delta );
        
        // remove duplicates
        if (i > 0)
        {
            if (coord[2*pos] != temp1 || coord[(2*pos)+1] != temp2 )
            {
                pos++;
                coord[2*pos] = temp1;
                coord[(2*pos)+1] = temp2;
            }
        }
        else
        {
            coord[2*i] = temp1;
            coord[(2*i)+1] = temp2;
        }
        
    }
    class Point* gridCurve = new class Point(curve->getID(), coord, this->maxCurvePoints, curve);
    return gridCurve;
}

template<>
class Curve* gridCurve<class LSH<class Curve*> >::findNN(class Curve* query, double* dist)
{
    class Point* queryGridCurve;
    class Curve* temp, *neighbor = NULL;
    double minDistance = numeric_limits<double>::max();

    for(int i = 0; i < L; i++)
    {
        queryGridCurve = createVector(query, i);
        temp = algorithm[i]->approximateNN(queryGridCurve, dist);
        if(*dist < minDistance){
            minDistance = *dist;
            neighbor = temp;
        }
    }
    return neighbor;
}


template<class T>
class Curve* gridCurve<T>::findNN(class Curve* query, double* distance)
{return NULL;}


template<class T>
gridCurve<T>::~gridCurve()
{
    for (int i = 0; i < L; i++)
    {
        delete displacement[i];
        delete points[i];
        delete algorithm[i];
    }

    delete [] displacement;
    delete [] points;
    delete [] algorithm;
}

template class gridCurve<class LSH<class Curve*> >;
template class gridCurve<class Cube<class Curve*> >;
