#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>
#include <string>
using std::string;
#include <utility>
using std::pair;
#include <vector>
using std::vector;

class Curve{
    string ID;
    pair<double, double>* coordinates;
    int size;

    public:
    Curve(){};
    ~Curve();
    Curve(string,pair <double,double>*,int);
    pair <double,double>* getCoord();
    int getSize();
    string getID();
};


class Point
{
    string ID;
    double *coordinates;
    int size;
    class Curve *curvePtr;

public:
    Point();
    Point(string ID, double *coord, int siz,class Curve*);
    ~Point();
    string getID();
    double *getCoord();
    int getSize();
    class Curve* getCurvePtr();

};

template <class T>
class gridCurve
{
    vector<class Curve*>* curves;
    vector<class Point*>* points;
    int k;
    int L;
    int w;
    int probes;
    int maxCurvePoints;
    int minCurvePoints;
    int delta;
    double **displacement;
    T* algorithm;

    public:
    gridCurve(){};
    ~gridCurve();
    gridCurve(vector<class Curve*>*, int, int, int, int, int, int, string algorithm);
    class Point* createVector(class Curve* curve,int hashtableNo);
    pair <double,double>* getCoord();
    int getSize();
    string getID();
};


#endif