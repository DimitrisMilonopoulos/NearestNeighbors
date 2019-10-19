#ifndef POINT_HPP
#define POINT_HPP

#include <string>
#include <iostream>
#include <utility>


using namespace std;

//temporary class will be merged later
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
};


#endif